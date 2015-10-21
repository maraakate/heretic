@ECHO OFF
echo Pick 1 for Original
echo Pick 2 for Updated 1.3a
echo Pick Q to Quit
choice /c:q12
if errorlevel 3 goto updated
if errorlevel 2 goto original
if errorlevel 1 goto end
:original
COPY /Y HERETIC.ORG HERETIC.EXE
goto end
:updated
COPY /Y HERETIC.UPD HERETIC.EXE
goto end
:end
