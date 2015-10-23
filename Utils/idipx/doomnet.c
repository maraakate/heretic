#include <io.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <process.h>
#include <conio.h>
#include <dos.h>

#include "doomnet.h"
#include "ipxstr.h"
//#include "ipx_frch.h"		// FRENCH VERSION

doomcom_t doomcom;
int            vectorishooked;
int	myargc1;
char **myargv1;
void interrupt (*olddoomvect) (void);



/*
=============
=
= LaunchDOOM
=
These fields in doomcom should be filled in before calling:

     short     numnodes;      // console is allways node 0
     short     ticdup;             // 1 = no duplication, 2-5 = dup for 
slow nets
     short     extratics;          // 1 = send a backup tic in every 
packet

	 short     consoleplayer; // 0-3 = player number
	 short     numplayers;         // 1-4
	 short     angleoffset;   // 1 = left, 0 = center, -1 = right
	 short     drone;              // 1 = drone
=============
*/

void LaunchDOOM (void)
{
	char *newargs[1024];
	char exeargs[99], exenew[99]; // FS: Pass a custom EXE
	char adrstring[10];
	long      flatadr;
	int i, z;

// prepare for DOOM
	 doomcom.id = DOOMCOM_ID;

// hook the interrupt vector
	 olddoomvect = getvect (doomcom.intnum);
     setvect (doomcom.intnum,(void interrupt (*)(void))MK_FP(_CS, 
(int)NetISR));
     vectorishooked = 1;

// build the argument list for DOOM, adding a -net &doomcom
     memcpy (newargs, _argv, (_argc+1)*2);
	 newargs[_argc] = "-net";
	 flatadr = (long)_DS*16 + (unsigned)&doomcom;
	 sprintf (adrstring,"%lu",flatadr);
	 newargs[_argc+1] = adrstring;
	 newargs[_argc+2] = NULL;
/*
	 if (!access("doom2.exe",0))
		spawnv  (P_WAIT, "doom2", newargs);
	 else
		spawnv  (P_WAIT, "doom", newargs);
*/
	 myargc1 = _argc;
	 myargv1 = _argv;

	if((i = CheckParm("-exe")) != 0)
	{
		strcpy(exeargs, myargv1[i+1]);
		printf("USING CUSTOM EXE: %s\n", exeargs);
		for (z = 0; z < strlen(exeargs)-4; z++)
		{
			exenew[z] = toupper(exeargs[z]);
			exenew[z+1] = '\0';
		}
	}
	else
	{
		if(!access("doomnew.exe",0)) // FS: Look for my updated v1.9a first
		{
			strcpy(exeargs, "DOOMNEW.EXE");
			strcpy(exenew, "DOOMNEW");
		}
		else if(!access("heretic.exe",0))
		{
			strcpy(exeargs, "HERETIC.EXE");
			strcpy(exenew, "HERETIC");
		}
		else if (!access("doom2.exe",0))
		{
			strcpy(exeargs, "DOOM2.EXE");
			strcpy(exenew, "DOOM2");
		}
		else if (!access("doom.exe",0))
		{
			strcpy(exeargs, "DOOM.EXE");
			strcpy(exenew, "DOOM");
		}
		else
		{
			Error("Unable to find Heretic, Doom 2, or Doom!");
		}
	}

	if(!access(exeargs,0))
		spawnv  (P_WAIT, exenew, newargs);
	else
	{
		Error("Unable to find %s", exeargs);
	}

	 #ifdef DOOM2
		 printf (STR_RETURNED"\n");
	 #else
		printf ("Returned from %s\n", exenew);
	 #endif
}

