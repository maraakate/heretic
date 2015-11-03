@echo off
wmake -f makefile.wat clean
wmake -f makefile.wat tic.exe

md release
copy heretic.exe release
copy readme.htc release
copy ipxnew.exe release
copy ipxnew.txt release
copy lcdbios.exe release
copy readme.vr release
copy stereo.bat release

"C:\PROGRAM FILES\7-zip\7z.exe" a -mx9 -mmt "F:\PROJ\HERETIC\HERETIC_EXE_LATEST.7Z" "F:\PROJ\HERETIC\RELEASE\*"

rd /s /q F:\PROJ\HERETIC\RELEASE
