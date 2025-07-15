@echo off
cd /d "%~dp0"
python --version >nul 2>&1
IF %ERRORLEVEL% NEQ 0 (
  echo Python n'est pas installe.
  start https://www.python.org/downloads/windows/
  pause
  exit
) ELSE (
  echo Python est installe
)
IF EXIST requirements.txt (
  echo Installation des bibliotheques...
  pip install -r requirements.txt
) ELSE (
  echo Le fichier requirements.txt est introuvable.
  echo numpy, scipy, pyserial, pyAudioWpatch
)
echo Lancement du programme...
python beat.py --port COM7 --baudrate 115200 --bp-low 30 --bp-high 100 --k-high 1.4 --k-low 0.9 --min-interval 0.4 --bp-order 1
pause
