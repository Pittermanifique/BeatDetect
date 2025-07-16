!define APP_NAME "BeatDetect"
!define APP_VERSION "1.3.0"
!define APP_PUBLISHER "Pittermanifique"
!define INSTALL_DIR "$PROGRAMFILES\${APP_NAME}"

Outfile "${APP_NAME}_Installer.exe"
InstallDir "${INSTALL_DIR}"
RequestExecutionLevel admin

; Icônes pour l’installateur et le désinstalleur
Icon "icone.ico"
UninstallIcon "icone.ico"

; Pages standards
Page directory
Page instfiles
UninstPage uninstConfirm
UninstPage instfiles

Section "Install"

  SetOutPath "$INSTDIR"

  ; Copie tous les fichiers (assure-toi que le script est dans le bon dossier)
  File /r *.*

  ; Copie l’icône dans le dossier d’installation
  File "icone.ico"

  ; Créer raccourcis
  CreateShortCut "$DESKTOP\${APP_NAME}.lnk" "$INSTDIR\appbeat\build\Desktop_Qt_6_9_1_MinGW_64_bit-Release\release\appbeat.exe" "" "$INSTDIR\icone.ico"
  CreateDirectory "$SMPROGRAMS\${APP_NAME}"
  CreateShortCut "$SMPROGRAMS\${APP_NAME}\${APP_NAME}.lnk" "$INSTDIR\appbeat\build\Desktop_Qt_6_9_1_MinGW_64_bit-Release\release\appbeat.exe" "" "$INSTDIR\icone.ico"

  ; Enregistre le désinstalleur
  WriteUninstaller "$INSTDIR\Uninstall.exe"

  ; Écrit dans le registre pour apparaître dans “Programmes et fonctionnalités”
  WriteRegStr HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\${APP_NAME}" "DisplayName" "${APP_NAME} ${APP_VERSION}"
  WriteRegStr HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\${APP_NAME}" "UninstallString" "$INSTDIR\Uninstall.exe"
  WriteRegStr HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\${APP_NAME}" "DisplayIcon" "$INSTDIR\icon.ico"
  WriteRegStr HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\${APP_NAME}" "Publisher" "${APP_PUBLISHER}"
  WriteRegStr HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\${APP_NAME}" "InstallLocation" "$INSTDIR"
  WriteRegStr HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\${APP_NAME}" "Version" "${APP_VERSION}"

SectionEnd

Section "Uninstall"

  ; Supprime les fichiers
  Delete "$INSTDIR\appbeat\build\Desktop_Qt_6_9_1_MinGW_64_bit-Release\release\appbeat.exe"
  Delete "$INSTDIR\icone.ico"
  Delete "$INSTDIR\Uninstall.exe"
  RMDir /r "$INSTDIR"

  ; Supprime les raccourcis
  Delete "$DESKTOP\${APP_NAME}.lnk"
  Delete "$SMPROGRAMS\${APP_NAME}\${APP_NAME}.lnk"
  RMDir "$SMPROGRAMS\${APP_NAME}"

  ; Supprime la clé de désinstallation
  DeleteRegKey HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\${APP_NAME}"

SectionEnd
