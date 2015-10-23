#include <stdio.h>
#include <io.h>
#include <stdlib.h>
#include <string.h>
#include <process.h>
#include <dos.h>
#include "doomnet.h"
#include "sermain.h"

#ifdef FRENCH
#include "ser_frch.h"		// FRENCH VERSION
#else
#include "serstr.h"			// ENGLISH VERSION
#endif

extern	int	myargc;
extern	char **myargv;

doomcom_t	doomcom;
int			vectorishooked;
void interrupt (*olddoomvect) (void);



/*
=================
=
= CheckParm
=
= Checks for the given parameter in the program's command line arguments
=
= Returns the argument number (1 to argc-1) or 0 if not present
=
=================
*/

int CheckParm (char *check)
{
	int             i;

	for (i = 1;i<myargc;i++)
		if ( !stricmp(check,myargv[i]) )
			return i;

	return 0;
}

void BuildResponseFile(char **args,int argc)
{
	int	p;
	int	doom2;
	int	heretic;
	int	doom;
	int	i;
	FILE	*fp;

	doom2 = access("doom2.exe",0);
	doom = access("doom.exe",0);
	heretic = access("heretic.exe",0);

	if (doom2)
		args[0] = "doom2.exe";
	else
	if (doom)
		args[0] = "doom.exe";
	else
	if (heretic)
		args[0] = "heretic.exe";

	fp = fopen("idser.rsp","w+t");
	if (fp == NULL)
		exit(1);

//	for (i = 1;i < argc;i++)
//		printf("arg[%d] = %s\n",i,args[i]);
//	getch();

	for (i = 1;i < argc;i++)
	{
		if (!strcmp(args[i],"-warp"))
		{
			if (doom2)
			{
				fprintf(fp,"%s %s\n",args[i],args[i+1]);
				i++;
			}
			else
			{
				fprintf(fp,"%s %s %s\n",args[i],args[i+1],args[i+2]);
				i += 2;
			}
		}
		else
		if (!strcmp(args[i],"-file"))
		{
			i++;
			fprintf(fp,"-file ");
			while(args[i][0]!='-' && i<argc)
				fprintf(fp,"%s ",args[i++]);
			fprintf(fp,"\n");
			i--;
		}
		else
		if ((!strcmp(args[i],"-config")) ||
			(!strcmp(args[i],"-debugfile")) ||
			(!strcmp(args[i],"-episode")) ||
			(!strcmp(args[i],"-loadgame")) ||
			(!strcmp(args[i],"-net")) ||
			(!strcmp(args[i],"-playdemo")) ||
			(!strcmp(args[i],"-record")) ||
			(!strcmp(args[i],"-dial")) ||
			(!strcmp(args[i],"-timer")) ||
			(!strcmp(args[i],"-turbo")) ||
			(!strcmp(args[i],"-skill")))
		{
			fprintf(fp,"%s %s\n",args[i],args[i+1]);
			i++;
		}
		else
			fprintf(fp,"%s\n",args[i]);
	}

	fclose(fp);
}

/*
=============
=
= LaunchDOOM
=
These fields in doomcom should be filled in before calling:

	short	numnodes;		// console is allways node 0
	short	ticdup;			// 1 = no duplication, 2-5 = dup for slow nets
	short	extratics;		// 1 = send a backup tic in every packet

	short	consoleplayer;	// 0-3 = player number
	short	numplayers;		// 1-4
	short	angleoffset;	// 1 = left, 0 = center, -1 = right
	short	drone;			// 1 = drone
=============
*/

void LaunchDOOM (void)
{
	int	i;
	char	*newargs[99];
	char	adrstring[10];
	long  	flatadr;
	int		p;
	unsigned char	far	*vector;

	gotoxy(oldx,oldy);

// prepare for DOOM
	doomcom.id = DOOMCOM_ID;

// hook an interrupt vector
	p= CheckParm ("-vector");

	if (p)
	{
		doomcom.intnum = sscanf ("0x%x",_argv[p+1]);
	}
	else
	{
		for (doomcom.intnum = 0x60 ; doomcom.intnum <= 0x66 ; doomcom.intnum++)
		{
			vector = *(char far * far *)(doomcom.intnum*4);
			if ( !vector || *vector == 0xcf )
				break;
		}
		if (doomcom.intnum == 0x67)
		{
			printf (STR_WARNING);
			doomcom.intnum = 0x66;
		}
	}
	printf (STR_COMM"\n",doomcom.intnum);

	olddoomvect = getvect (doomcom.intnum);
	setvect (doomcom.intnum,NetISR);
	vectorishooked = 1;

// build the argument list for DOOM, adding a -net &doomcom

	memcpy (newargs, myargv, (myargc+1)*2);
	newargs[myargc] = "-net";
	flatadr = (long)_DS*16 + (unsigned)&doomcom;
	sprintf (adrstring,"%lu",flatadr);
	newargs[myargc+1] = adrstring;
	newargs[myargc+2] = NULL;

	BuildResponseFile(newargs,myargc+2);
	newargs[1] = "@idser.rsp";
	newargs[2] = NULL;

	if (!access("doom2.exe",0))
		spawnv  (P_WAIT, "doom2.exe", newargs);
	else
	if (!access("heretic.exe",0))
		spawnv(P_WAIT,"heretic.exe", newargs);
	else
		spawnv  (P_WAIT, "doom.exe", newargs);

	gotoxy(oldx,oldy);
	printf (STR_RETURNED"\n");
	DrawPanel();
}


