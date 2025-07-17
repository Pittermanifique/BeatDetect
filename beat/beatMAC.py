import sys
import time
import serial
import argparse
import numpy as np
import pyaudio as pa
from scipy.signal import butter, lfilter
import glob

def list_serial_ports():
    return glob.glob('/dev/tty.*')

def parse_args():
    p = argparse.ArgumentParser(
        description="Détection de kicks via spectral overflow et envoi série (compatible macOS)"
    )

    default_ports = list_serial_ports()
    default_port = default_ports[0] if default_ports else '/dev/tty.usbserial'

    p.add_argument('--port', type=str, default=default_port,
                   help=f"Port série (ex: {default_port})")
    p.add_argument('--baudrate', type=int, default=115200,
                   help="Baudrate du port série")
    p.add_argument('--timeout', type=float, default=1.0,
                   help="Timeout pour le port série (s)")

    # Audio
    p.add_argument('--rate', type=int, default=44100,
                   help="Fréquence d'échantillonnage")
    p.add_argument('--chunk', type=int, default=512,
                   help="Taille de la fenêtre d’analyse")
    p.add_argument('--hop', type=int, default=None,
                   help="Pas de lecture (par défaut chunk//2)")

    # Spectral Flux
    p.add_argument('--hist-sec', type=float, default=1.0)
    p.add_argument('--k-high', type=float, default=1.3)
    p.add_argument('--k-low', type=float, default=0.8)
    p.add_argument('--min-interval', type=float, default=0.18)
    p.add_argument('--rms-th', type=float, default=0.01)
    p.add_argument('--abs-flux-th', type=float, default=0.05)

    # Filtre passe-bande
    p.add_argument('--bp-low', type=float, default=40.0)
    p.add_argument('--bp-high', type=float, default=80.0)
    p.add_argument('--bp-order', type=int, default=1)

    return p.parse_args()

def select_input_device(p):
    print("\n🔊 Périphériques audio disponibles :")
    for i in range(p.get_device_count()):
        info = p.get_device_info_by_index(i)
        if info['maxInputChannels'] > 0:
            print(f"{i}: {info['name']}")

    index = int(input("➡️  Entrez l’index du périphérique d'entrée à utiliser : "))
    return p.get_device_info_by_index(index)

def main():
    args = parse_args()

    print(f"🔌 Port série choisi : {args.port}")
    try:
        ser = serial.Serial(args.port, args.baudrate, timeout=args.timeout)
    except Exception as e:
        print(f"❌ Erreur ouverture port série : {e}")
        sys.exit(1)

    RATE = args.rate
    CHUNK = args.chunk
    HOP = args.hop if args.hop else CHUNK // 2
    HIST_FRAMES = int(args.hist_sec / (HOP / RATE))
    b_bp, a_bp = butter(args.bp_order, [args.bp_low / (RATE / 2), args.bp_high / (RATE / 2)], btype='band')

    p = pa.PyAudio()
    input_dev = select_input_device(p)

    stream = p.open(
        format=pa.paInt16,
        channels=input_dev['maxInputChannels'],
        rate=int(input_dev['defaultSampleRate']),
        input=True,
        frames_per_buffer=HOP,
        input_device_index=input_dev['index']
    )

    prev_spectrum = np.zeros(CHUNK // 2 + 1, dtype=np.float32)
    flux_history = []
    last_beat_time = 0.0
    is_armed = True
    buffered = np.zeros((CHUNK, input_dev['maxInputChannels']), dtype=np.float32)
    offset = 0

    print("🎧 Démarrage de la détection… Ctrl+C pour stopper.")
    try:
        while True:
            data = stream.read(HOP, exception_on_overflow=False)
            chunk = (np.frombuffer(data, np.int16).astype(np.float32)
                     / np.iinfo(np.int16).max)
            chunk = chunk.reshape(-1, input_dev['maxInputChannels'])

            buffered[offset:offset+HOP] = chunk
            offset = (offset + HOP) % CHUNK
            mono = buffered.mean(axis=1)

            rms = np.sqrt(np.mean(mono ** 2))
            now = time.time()

            if rms < args.rms_th:
                is_armed = True
                ser.write(b"0\n")
                continue

            mono_f = lfilter(b_bp, a_bp, mono)
            spectrum = np.abs(np.fft.rfft(mono_f))
            flux = np.sum(np.maximum(spectrum - prev_spectrum, 0))
            prev_spectrum = spectrum

            flux_history.append(flux)
            if len(flux_history) > HIST_FRAMES:
                flux_history.pop(0)

            mu, sigma = np.mean(flux_history), np.std(flux_history)
            high_thresh = mu + args.k_high * sigma
            low_thresh = mu + args.k_low * sigma
            interval_ok = (now - last_beat_time) > args.min_interval

            if flux > high_thresh and flux > args.abs_flux_th and is_armed and interval_ok:
                ser.write(b"1\n")
                last_beat_time = now
                is_armed = False
            elif flux > high_thresh and flux > args.abs_flux_th and is_armed and not interval_ok:
                ser.write(b"0\n")
            elif flux < low_thresh and interval_ok:
                is_armed = True
                ser.write(b"0\n")

    except KeyboardInterrupt:
        print("\n🛑 Arrêt demandé.")
    finally:
        ser.write(b"0\n")
        stream.stop_stream()
        stream.close()
        p.terminate()
        ser.close()
        print("✅ Terminé.")

if __name__ == '__main__':
    main()
