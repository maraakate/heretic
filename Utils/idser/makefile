# ********************** START OF TEST232.MAK **********************
#
#
# This is the make file for the RS232 class test program.
# Just remove the leading comment line from your compiler, then
# execute:
#          Borland and Zortech:  make -ftest232.mak
#
#          Microsoft:            nmake -ftest232.mak
#

#CC = tcc -w
CC = bcc -w
#CC = ztc -b
#CC = cl /W4
#CC = wcl386 

FILES = pc8250.obj queue.obj isr_8250.obj pcirq.obj

.cpp.obj:
  $(CC) -c -Ic:\tc\include $<

test232.exe : test232.obj rs232.obj textwind.obj msdos.obj $(FILES)
             $(CC) -Lg:\bc31\lib test232.obj rs232.obj textwind.obj msdos.obj $(FILES)

# ********************** END OF TEST232.MAK **********************

