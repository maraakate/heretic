@echo off
wmake -f makefile.vr clean
wmake -f makefile.vr ticvr.exe

md release
copy lcdbios.exe release
copy herevr.exe release
copy readme.vr release
copy stereo.bat release

"C:\PROGRAM FILES\7-zip\7z.exe" a -mx9 -mmt "F:\PROJ\HERETIC\HEREVR_EXE_LATEST.7Z" "F:\PROJ\HERETIC\RELEASE\*"

rd /s /q F:\PROJ\HERETIC\RELEASE
