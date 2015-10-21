@echo off

if "%1"=="/?" goto usage
if "%1"=="final" goto final
if "%1"=="FINAL" goto final
if "%1"=="debug" goto debug
if "%1"=="DEBUG" goto debug
if "%1"=="clean" goto clean
if "%1"=="CLEAN" goto clean

:usage
echo.
echo Heretic v1.3 make batch
echo Usage: build [/?] [build-type]
echo.
echo build-type FINAL = Final build
echo build-type DEBUG = Debug build (include debugging info)
echo build-type CLEAN = Clean build environment
echo.
goto end

:final
echo.
echo.
echo *** Building Heretic v1.3 Final executable
echo.
echo.
wmake -f makefile.wat clean
wmake -f makefile.wat tic.exe %1 %2 %3 %4 %5 %6 %7 %8 %9
goto end

:debug
echo.
echo.
echo *** Building Heretic v1.3 Debug executable
echo.
echo.
wmake -f makefile.wat clean
wmake -f makefile.wat tic.exe EXTERNOPT=/d2 %1 %2 %3 %4 %5 %6 %7 %8 %9
goto end

:clean
echo.
echo.
echo *** Cleaning Heretic v1.3 Environment (no binary deletion)
echo.
echo.
wmake -f makefile.wat clean
goto end

:end
