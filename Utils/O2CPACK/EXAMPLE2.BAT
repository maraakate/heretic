@rem This file is part of the Object to Coff (O2C) package
@rem -----------------------------------------------------

@echo off
echo Making & Running example 2 (for djgpp 2)
echo Running assembler
tasm example2.asm /m /ml

echo Making library file
tlib example2.lib +example2.obj

echo Running converter
call o2c -C example2.lib

echo Running compiler
gcc example.c example2.a

echo Running program
a.exe

del a.out
del a.exe
del example2.a
del example2.lib
del example2.obj
echo.

