# Cubes setup for Windows

RequestExecutionLevel admin

Name Cubes

# General Symbol Definitions
!define REGKEY "SOFTWARE\$(^Name)"
#!define VERSION 0.0.12
#!define BUILD_TYPE Release
!define COMPANY bigfatbrowncat
!define URL http://github.com/bigfatbrowncat

# MultiUser Symbol Definitions
!define MULTIUSER_EXECUTIONLEVEL Admin
!define MULTIUSER_MUI
!define MULTIUSER_INSTALLMODE_DEFAULT_REGISTRY_KEY "${REGKEY}"
!define MULTIUSER_INSTALLMODE_DEFAULT_REGISTRY_VALUENAME MultiUserInstallMode
!define MULTIUSER_INSTALLMODE_COMMANDLINE
!define MULTIUSER_INSTALLMODE_INSTDIR Cubes
!define MULTIUSER_INSTALLMODE_INSTDIR_REGISTRY_KEY "${REGKEY}"
!define MULTIUSER_INSTALLMODE_INSTDIR_REGISTRY_VALUE "Path"

# MUI Symbol Definitions
!define MUI_ICON ..\icon\Cubes.ico
!define MUI_FINISHPAGE_NOAUTOCLOSE
!define MUI_STARTMENUPAGE_REGISTRY_ROOT HKLM
!define MUI_STARTMENUPAGE_REGISTRY_KEY ${REGKEY}
!define MUI_STARTMENUPAGE_REGISTRY_VALUENAME StartMenuGroup
!define MUI_STARTMENUPAGE_DEFAULTFOLDER Cubes
!define MUI_UNICON ..\icon\Cubes.ico
!define MUI_UNFINISHPAGE_NOAUTOCLOSE
!define MUI_LANGDLL_REGISTRY_ROOT HKLM
!define MUI_LANGDLL_REGISTRY_KEY ${REGKEY}
!define MUI_LANGDLL_REGISTRY_VALUENAME InstallerLanguage

# Included files
!include MultiUser.nsh
!include Sections.nsh
!include MUI2.nsh

# Reserved Files
!insertmacro MUI_RESERVEFILE_LANGDLL

# Variables
Var StartMenuGroup

# Installer pages
!insertmacro MUI_PAGE_WELCOME
!insertmacro MUI_PAGE_LICENSE ..\sfmlcube\license.txt
!insertmacro MUI_PAGE_LICENSE ..\SFML-2.0\license.txt
!insertmacro MULTIUSER_PAGE_INSTALLMODE
!insertmacro MUI_PAGE_COMPONENTS
!insertmacro MUI_PAGE_DIRECTORY
!insertmacro MUI_PAGE_STARTMENU Application $StartMenuGroup
!insertmacro MUI_PAGE_INSTFILES

# Installer sections
Section $(^Cubes) SEC0000
    SectionIn RO
    SetOutPath $INSTDIR
    SetOverwrite on
    File /r ..\sfmlcube\res
    File ..\sfmlcube\MinGW-${BUILD_TYPE}\sfmlcube.exe
SectionEnd

!define MUI_FINISHPAGE_RUN "$INSTDIR\sfmlcube.exe"
!insertmacro MUI_PAGE_FINISH
!insertmacro MUI_UNPAGE_CONFIRM
!insertmacro MUI_UNPAGE_INSTFILES

# Installer languages
!insertmacro MUI_LANGUAGE English
!insertmacro MUI_LANGUAGE Russian

# Installer attributes

OutFile out/${BUILD_TYPE}/Cubes-${VERSION}-win-x86-setup.exe
InstallDir Cubes
CRCCheck on
XPStyle on
ShowInstDetails show
VIProductVersion ${VERSION}.0
VIAddVersionKey /LANG=${LANG_ENGLISH} ProductName Cubes
VIAddVersionKey /LANG=${LANG_ENGLISH} ProductVersion "${VERSION}"
VIAddVersionKey /LANG=${LANG_ENGLISH} CompanyName "${COMPANY}"
VIAddVersionKey /LANG=${LANG_ENGLISH} CompanyWebsite "${URL}"
VIAddVersionKey /LANG=${LANG_ENGLISH} FileVersion "${VERSION}"
VIAddVersionKey /LANG=${LANG_ENGLISH} FileDescription ""
VIAddVersionKey /LANG=${LANG_ENGLISH} LegalCopyright ""
InstallDirRegKey HKLM "${REGKEY}" Path
ShowUninstDetails show

Section -post SEC0001
    SetShellVarContext all
    WriteRegStr HKLM "${REGKEY}" Path $INSTDIR
    SetOutPath $INSTDIR
    WriteUninstaller $INSTDIR\uninstall.exe
    !insertmacro MUI_STARTMENU_WRITE_BEGIN Application
    SetOutPath $SMPROGRAMS\$StartMenuGroup
    CreateShortcut "$SMPROGRAMS\$StartMenuGroup\$(^UninstallLink).lnk" $INSTDIR\uninstall.exe
    CreateShortcut "$SMPROGRAMS\$StartMenuGroup\$(^CubesLink).lnk" $INSTDIR\sfmlcube.exe
    !insertmacro MUI_STARTMENU_WRITE_END
    WriteRegStr HKLM "SOFTWARE\Microsoft\Windows\CurrentVersion\Uninstall\$(^Name)" DisplayName "$(^Name)"
    WriteRegStr HKLM "SOFTWARE\Microsoft\Windows\CurrentVersion\Uninstall\$(^Name)" DisplayVersion "${VERSION}"
    WriteRegStr HKLM "SOFTWARE\Microsoft\Windows\CurrentVersion\Uninstall\$(^Name)" Publisher "${COMPANY}"
    WriteRegStr HKLM "SOFTWARE\Microsoft\Windows\CurrentVersion\Uninstall\$(^Name)" URLInfoAbout "${URL}"
    WriteRegStr HKLM "SOFTWARE\Microsoft\Windows\CurrentVersion\Uninstall\$(^Name)" DisplayIcon $INSTDIR\uninstall.exe
    WriteRegStr HKLM "SOFTWARE\Microsoft\Windows\CurrentVersion\Uninstall\$(^Name)" UninstallString $INSTDIR\uninstall.exe
    WriteRegDWORD HKLM "SOFTWARE\Microsoft\Windows\CurrentVersion\Uninstall\$(^Name)" NoModify 1
    WriteRegDWORD HKLM "SOFTWARE\Microsoft\Windows\CurrentVersion\Uninstall\$(^Name)" NoRepair 1
SectionEnd

Section /o $(^DesktopShortcut) SEC0002  #"$(^DesktopShortcut)"
    SetShellVarContext all
    CreateShortCut "$DESKTOP\$(^CubesLinkDesktop).lnk" $INSTDIR\sfmlcube.exe
    WriteRegStr HKLM "${REGKEY}\Components" DesktopShortcut 1
SectionEnd

# Macro for selecting uninstaller sections
!macro SELECT_UNSECTION SECTION_ID UNSECTION_ID
    Push $R0
    ReadRegStr $R0 HKLM "${REGKEY}\Components" "${SECTION_ID}"
    StrCmp $R0 1 0 next${UNSECTION_ID}
    !insertmacro SelectSection "${UNSECTION_ID}"
    GoTo done${UNSECTION_ID}
next${UNSECTION_ID}:
    !insertmacro UnselectSection "${UNSECTION_ID}"
done${UNSECTION_ID}:
    Pop $R0
!macroend

# Uninstaller sections
Section -un.Cubes UNSEC0000
    Delete /REBOOTOK $INSTDIR\sfmlcube.exe
    RmDir /r /REBOOTOK $INSTDIR
    DeleteRegValue HKLM "${REGKEY}\Components" Cubes
SectionEnd

Section -un.post UNSEC0001
#    ${If} $MultiUser.InstallMode == 'AllUsers'
        SetShellVarContext all
#    ${ElseIf} $MultiUser.InstallMode == 'CurrentUser'
#        SetShellVarContext current
#    ${EndIf}
        
    Delete /REBOOTOK "$SMPROGRAMS\$StartMenuGroup\$(^UninstallLink).lnk"
    Delete /REBOOTOK "$SMPROGRAMS\$StartMenuGroup\$(^CubesLink).lnk"
    RmDir /REBOOTOK $SMPROGRAMS\$StartMenuGroup
    Delete /REBOOTOK $INSTDIR\uninstall.exe

    DeleteRegKey HKLM "SOFTWARE\Microsoft\Windows\CurrentVersion\Uninstall\$(^Name)"
    DeleteRegValue HKLM "${REGKEY}" StartMenuGroup
    DeleteRegValue HKLM "${REGKEY}" Path
    DeleteRegKey /IfEmpty HKLM "${REGKEY}\Components"
    DeleteRegKey /IfEmpty HKLM "${REGKEY}"

    RmDir /REBOOTOK $INSTDIR
    Push $R0
    StrCpy $R0 $StartMenuGroup 1
    StrCmp $R0 ">" no_smgroup
no_smgroup:
    Pop $R0
SectionEnd

Section /o -un.DesktopShortcut UNSEC0002
#    ${If} $MultiUser.InstallMode == 'AllUsers'
        SetShellVarContext all
#    ${ElseIf} $MultiUser.InstallMode == 'CurrentUser'
#        SetShellVarContext current
#    ${EndIf}

    Delete /REBOOTOK "$DESKTOP\$(^CubesLinkDesktop).lnk"
SectionEnd

# Sections descriptions
!insertmacro MUI_FUNCTION_DESCRIPTION_BEGIN
    !insertmacro MUI_DESCRIPTION_TEXT ${SEC0000} $(^CubesSectionDescription)
    !insertmacro MUI_DESCRIPTION_TEXT ${SEC0002} $(^DesktopShortcutDescription)
!insertmacro MUI_FUNCTION_DESCRIPTION_END

# Installer functions
Function .onInit
    InitPluginsDir
    !insertmacro MUI_LANGDLL_DISPLAY
    !insertmacro MULTIUSER_INIT
FunctionEnd

# Uninstaller functions
Function un.onInit
    !insertmacro MUI_STARTMENU_GETFOLDER Application $StartMenuGroup
    !insertmacro MUI_UNGETLANGUAGE
    !insertmacro MULTIUSER_UNINIT
    
    !insertmacro SelectSection "${UNSEC0000}"                       # The "Cubes" section isn't optional
    !insertmacro SELECT_UNSECTION DesktopShortcut ${UNSEC0002}
FunctionEnd

# Installer Language Strings

LangString ^UninstallLink ${LANG_ENGLISH} "Uninstall $(^Name)"
LangString ^UninstallLink ${LANG_RUSSIAN} "Удалить $(^Name)"

LangString ^CubesLink ${LANG_ENGLISH} "Play $(^Name)"
LangString ^CubesLink ${LANG_RUSSIAN} "Запустить $(^Name)"

LangString ^CubesLinkDesktop ${LANG_ENGLISH} "$(^Name)"
LangString ^CubesLinkDesktop ${LANG_RUSSIAN} "$(^Name)"

LangString ^DesktopShortcut ${LANG_ENGLISH} "Shortcut on desktop"
LangString ^DesktopShortcut ${LANG_RUSSIAN} "Ярлык на Рабочем столе"

LangString ^Cubes ${LANG_ENGLISH} "Cubes"
LangString ^Cubes ${LANG_RUSSIAN} "Cubes"

LangString ^DesktopShortcutDescription ${LANG_ENGLISH} "Select this if you want to create a shortcut to the game on your desktop"
LangString ^DesktopShortcutDescription ${LANG_RUSSIAN} "Выберите этот пункт, чтобы создать ярлык к игре на Рабочем столе"

LangString ^CubesSectionDescription ${LANG_ENGLISH} "The game files. Should be installed."
LangString ^CubesSectionDescription ${LANG_RUSSIAN} "Файлы игры. Установка обязательна."

