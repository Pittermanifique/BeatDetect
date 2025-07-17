#!/bin/bash

cd "$(dirname "$0")"

echo "=== Vérification de Homebrew ==="
if ! command -v brew &> /dev/null; then
    echo "Homebrew n'est pas installé. Installation en cours..."
    /bin/bash -c "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/HEAD/install.sh)"
    echo "Homebrew installé."
else
    echo "Homebrew est déjà installé."
fi

echo "=== Installation des dépendances système ==="
brew install portaudio

echo "=== Vérification de Python 3 ==="
if ! command -v python3 &> /dev/null; then
    echo "Python3 n'est pas installé. Installation via Homebrew..."
    brew install python
else
    echo "Python3 est installé."
fi

echo "=== Installation des dépendances Python ==="
if [ -f requirements_mac.txt ]; then
    python3 -m pip install --upgrade pip
    python3 -m pip install -r requirementMAC.txt
else
    echo "Fichier requirementMAC.txt introuvable. Création d'un fichier par défaut..."
    cat <<EOT > requirementMAC.txt
numpy
scipy
pyserial
pyaudio
EOT
    echo "Merci de vérifier requirementMAC.txt, puis relancer ce script."
    exit 1
fi

echo "=== Lancement du programme beat.py ==="
python3 beatMAC.py \
    --port /dev/tty.usbserial-xxxx \   # <-- adapte ce port à ton device
    --baudrate 115200 \
    --bp-low 30 \
    --bp-high 100 \
    --k-high 1.4 \
    --k-low 0.9 \
    --min-interval 0.4

echo "=== Fin du script ==="
