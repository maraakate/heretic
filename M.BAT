@REM Heretic make batch
@echo off

if "%1"=="/?" goto usage
if "%1"=="f" goto final
if "%1"=="F" goto final
if "%1"=="d" goto debug
if "%1"=="D" goto debug
if "%1"=="clean" goto clean

goto normal

:usage
echo.
echo Heretic make batch
echo Usage: M [/?] [build-type]
echo.
echo build-type f = Final build (no RANGECHECK)
echo build-type d = Debug build (include debugging info)
echo.
goto end

:final
echo.
echo.
echo *** Building Heretic FINAL executable
echo.
echo.
shift
wmake tic.exe EXTERNOPT=/dNORANGECHECKING %1 %2 %3 %4 %5 %6 %7 %8 %9
goto end

:debug
echo.
echo.
echo *** Building Heretic DEBUG executable
echo.
echo.
shift
wmake tic.exe EXTERNOPT=/d2 %1 %2 %3 %4 %5 %6 %7 %8 %9
goto end

:normal
echo.
echo.
echo *** Building Heretic DEVELOPMENT executable
echo.
echo.
wmake tic.exe %1 %2 %3 %4 %5 %6 %7 %8 %9
goto end

:clean
echo.
echo.
echo *** Cleaning Heretic Environment
echo.
echo.
wmake -f makefile clean
goto end

:end
