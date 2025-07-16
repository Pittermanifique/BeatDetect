!define APP_NAME "BeatDetect"
!define APP_VERSION "1.3.0"
!define APP_PUBLISHER "Pittermanifique"
!define INSTALL_DIR "$PROGRAMFILES\${APP_NAME}"

Outfile "${APP_NAME}_Installer.exe"
InstallDir "${INSTALL_DIR}"
RequestExecutionLevel admin

Page directory
Page instfiles
UninstPage uninstConfirm
UninstPage instfiles

Section "Install"

  SetOutPath $INSTDIR

  ; Copier tous les fichiers du dossier d'installation
  File /r "*.*"

  ; Créer un raccourci sur le bureau
  CreateShortCut "$DESKTOP\${APP_NAME}.lnk" "$INSTDIR\appbeat\build\Desktop_Qt_6_9_1_MinGW_64_bit-Release\release\appbeat.exe" "" "$INSTDIR\icon.ico"

  ; Créer un raccourci dans le menu Démarrer
  CreateDirectory "$SMPROGRAMS\${APP_NAME}"
  CreateShortCut "$SMPROGRAMS\${APP_NAME}\${APP_NAME}.lnk" "$INSTDIR\appbeat\build\Desktop_Qt_6_9_1_MinGW_64_bit-Release\release\appbeat.exe" "" "$INSTDIR\icon.ico"

  ; Enregistrer pour la désinstallation
  WriteUninstaller "$INSTDIR\Uninstall.exe"

SectionEnd

Section "Uninstall"

  ; Supprimer les fichiers
  Delete "$INSTDIR\appbeat\build\Desktop_Qt_6_9_1_MinGW_64_bit-Release\release\appbeat.exe"
  Delete "$INSTDIR\icon.ico"
  Delete "$INSTDIR\Uninstall.exe"
  RMDir /r "$INSTDIR"

  ; Supprimer les raccourcis
  Delete "$DESKTOP\${APP_NAME}.lnk"
  Delete "$SMPROGRAMS\${APP_NAME}\${APP_NAME}.lnk"
  RMDir "$SMPROGRAMS\${APP_NAME}"
  DeleteRegKey HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\APP_NAME"

SectionEnd
