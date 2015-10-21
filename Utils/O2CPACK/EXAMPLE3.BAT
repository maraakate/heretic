@rem This file is part of the Object to Coff (O2C) package
@rem -----------------------------------------------------

@echo off
echo Making & Running example 3 (for djgpp 2)
echo Running assembler
tasm example3.asm /m /ml

echo Running converter
call o2c example3.obj /Bexdata3.dat

echo Running compiler
gcc example.c example3.o exdata3.o

echo Running program
a.exe

del a.exe
del a.out
del example3.o
del exdata3.o
del example3.obj
echo.

