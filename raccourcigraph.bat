@echo off
set "TargetPath=%~dp0appbeat\build\Desktop_Qt_6_9_1_MinGW_64_bit-Release\release\appbeat.exe"
set "IconPath=%~dp0appbeat\build\Desktop_Qt_6_9_1_MinGW_64_bit-Release\release\icone.ico"  :: chemin vers ton icône .ico
set "ShortcutPath=%USERPROFILE%\Desktop\beatgraph.lnk"

powershell -command "$s=(New-Object -COM WScript.Shell).CreateShortcut('%ShortcutPath%');$s.TargetPath='%TargetPath%';$s.IconLocation='%IconPath%';$s.Save()"