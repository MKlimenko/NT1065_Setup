if not exist "%programfiles%\Module\NT1065_Setup" (mkdir "%programfiles%\Module\NT1065_Setup")
setx NT1065_Setup -m "%programfiles%\Module\NT1065_Setup"
copy src\NT1065_Setup.hpp "%programfiles%\Module\NT1065_Setup" > nul