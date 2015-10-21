@rem This file is part of the Object to Coff (O2C) package
@rem -----------------------------------------------------

@echo off
echo Making & Running example 1 (for djgpp 2)
echo Running assembler
tasm example1.asm /m /ml

echo Running converter
call o2c example1.obj

echo Running compiler
gcc example.c example1.o

echo Running program
a.exe

del a.out
del a.exe
del example1.o
del example1.obj
echo.

