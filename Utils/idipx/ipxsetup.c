// ipxsetup.c

//#define DOOM2
//#define HERETIC

#include <conio.h>
#include <stdio.h>
#include <stdlib.h>
#include <dos.h>
#include <string.h>
#include <process.h>
#include <stdarg.h>
#include <bios.h>

#include "ipxnet.h"
#include	"windows.h"
#ifdef FRENCH
#include "ipx_frch.h"	// FRENCH VERSION
#else
#include "ipxstr.h"
#endif

/*
#ifdef DOOM2
extern pup_t far panel2;
#define PANEL	panel2
#else
#ifdef HERETIC
extern pup_t far panelh;
#define PANEL panelh
#else
extern pup_t far panel1;
#define PANEL panel1
#endif
#endif
*/
extern pup_t far panel; // FS: Universal panel
#define PANEL panel

int gameid;
int numnetnodes;
int socketid = 0x869c;        // 0x869c is the official DOOM socket
int	myargc;
char **myargv;

setupdata_t    nodesetup[MAXNETNODES];

#define	HIDEX	54
#define	HIDEY	11
void hidecursor(void)
{
	gotoxy(HIDEX,HIDEY);
}

/*
=================
=
= Error
=
= For abnormal program terminations
=
=================
*/

void Error (char *error, ...)
{
     va_list argptr;

     if (vectorishooked)
          setvect (doomcom.intnum,olddoomvect);

     va_start (argptr,error);
     vprintf (error,argptr);
     va_end (argptr);
	 printf ("\n");
     ShutdownNetwork ();
     exit (1);
}


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

int CheckParm(char *parm)
     {
     int i;

	 for(i = 1; i < myargc; i++)
		  if(stricmp(parm, myargv[i]) == 0)
               return i;

     return 0;
     }


/*
=============
=
= NetISR
=
=============
*/

void interrupt NetISR (void)
{
     if (doomcom.command == CMD_SEND)
     {
          localtime++;
          SendPacket (doomcom.remotenode);
     }
	 else if (doomcom.command == CMD_GET)
     {
          GetPacket ();
     }
}



/*
===================
=
= LookForNodes
=
= Finds all the nodes for the game and works out player numbers among 
them
=
= Exits with nodesetup[0..numnodes] and nodeadr[0..numnodes] filled in
===================
*/

void LookForNodes (void)
{
     int             i,j,k;
     int             netids[MAXNETNODES];
     int             netplayer[MAXNETNODES];
	 struct time         time;
     int                 oldsec;
     setupdata_t         *setup, *dest;
     char           str[80];
     int            total, console;

	  int		curpx;
	  int		curpy;

#define	P2X	27
#define 	P2Y	13
#define	P3X	42
#define	P3Y	12
#define	P4X	42
#define	P4Y	13

#define	NAX	38			// number of players x
#define	NAY	11

#define	MSGX	34			// message area in window
#define	MSGY	14

	  int		xlist[3]=
				{P2X,P3X,P4X};
	  int		ylist[3]=
				{P2Y,P3Y,P4Y};
	  char	srchstr[]="-/|\\";
	  int		srchpos;
	  int		oldx;
	  int		oldy;
//
// wait until we get [numnetnodes] packets, then start playing
// the playernumbers are assigned by netid
//

	oldx = wherex();
	oldy = wherey();
	SaveScreen();
	DrawPup(&PANEL);
	textcolor(15);
	textbackground(1);
	gotoxy(NAX,NAY);
	cprintf("%d",numnetnodes);
	if (numnetnodes < 4)
	{
		gotoxy(P4X-1,P4Y);
		cprintf("            ");
	}
	if (numnetnodes < 3)
	{
		gotoxy(P3X-1,P3Y);
		cprintf("            ");
	}
	srchpos = 0;
	curpx = xlist[0];
	curpy = ylist[0];
	gotoxy(MSGX,MSGY);
	textcolor(14);
	cprintf("Searching...");

	  oldsec = -1;
	  setup = (setupdata_t *)&doomcom.data;
	  localtime = -1;          // in setup time, not game time

//
// build local setup info
//
     nodesetup[0].nodesfound = 1;
	 nodesetup[0].nodeswanted = numnetnodes;
     doomcom.numnodes = 1;

	  do
     {
//
// check for aborting
//
          while ( bioskey(1) )
          {
					if ( (bioskey (0) & 0xff) == 27)
					{
						RestoreScreen();
						gotoxy(oldx,oldy);
						Error ("\n"STR_NETABORT);
					}
		  }

//
// listen to the network
//
		  while (GetPacket ())
		  {
			   if (doomcom.remotenode == -1)
					dest = &nodesetup[doomcom.numnodes];
			   else
					dest = &nodesetup[doomcom.remotenode];

			   if (remotetime != -1)
			   {    // an early game packet, not a setup packet
					if (doomcom.remotenode == -1)
					{
						RestoreScreen();
						gotoxy(oldx,oldy);
						Error (STR_UNKNOWN);
					}
			// if it allready started, it must have found all nodes
			 dest->nodesfound = dest->nodeswanted;
			 continue;
			 }

	       // update setup ingo
	       memcpy (dest, setup, sizeof(*dest) );

			 if (doomcom.remotenode != -1)
		    continue;           // allready know that node address

	       //
	       // this is a new node
	       //
		   memcpy (&nodeadr[doomcom.numnodes], &remoteadr
               , sizeof(nodeadr[doomcom.numnodes]) );

               //
               // if this node has a lower address, take all startup info
               //
               if ( memcmp (&remoteadr, &nodeadr[0], sizeof(&remoteadr) ) 
< 0 )
					{
					}

					doomcom.numnodes++;

					gotoxy(curpx,curpy);
					textcolor(14);
					if (doomcom.numnodes > numnetnodes)
						cprintf("Extra node!");
					else
					{
						char far *screen;
						screen = MK_FP(0xb800,((curpy-1)*160)+((curpx-1)*2));
						*screen = 7;
					}
					curpx = xlist[doomcom.numnodes-1];
					curpy = ylist[doomcom.numnodes-1];
					gotoxy(MSGX,MSGY);
					cprintf("Found a node!");
					hidecursor();
					for (i = 1000;i < 2000;i += 100)
					{
						sound(i);
						delay(30);
					}
					nosound();

					if (doomcom.numnodes < numnetnodes)
					{
						gotoxy(MSGX,MSGY);
						cprintf("Searching... ");
						hidecursor();
					}
			 }
//
// we are done if all nodes have found all other nodes
//
			 for (i=0 ; i<doomcom.numnodes ; i++)
					if (nodesetup[i].nodesfound != nodesetup[i].nodeswanted)
						  break;

		  if (i == nodesetup[0].nodeswanted)
				break;         // got them all

//
// send out a broadcast packet every second
//
		  gettime (&time);
		  if (time.ti_sec == oldsec)
				continue;
		  oldsec = time.ti_sec;

			gotoxy(curpx,curpy);
			cprintf("%c",srchstr[srchpos++]);
			srchpos &= 3;
			hidecursor();
			sound(500);
			delay(10);
			nosound();


		  doomcom.datalength = sizeof(*setup);

		  nodesetup[0].nodesfound = doomcom.numnodes;

		  memcpy (&doomcom.data, &nodesetup[0], sizeof(*setup));

		  SendPacket (MAXNETNODES);     // send to all

	 } while (1);

	RestoreScreen();
	gotoxy(oldx,oldy);
//
// count players
//
	 total = 0;
	 console = 0;

     for (i=0 ; i<numnetnodes ; i++)
     {
          if (nodesetup[i].drone)
               continue;
          total++;
          if (total > MAXPLAYERS)
			   Error (STR_MORETHAN,MAXPLAYERS);
			 if (memcmp (&nodeadr[i], &nodeadr[0], sizeof(nodeadr[0])) < 0)
               console++;
     }


     if (!total)
		  Error (STR_NONESPEC);
	 if((i = CheckParm("-player")) != 0) // FS: Set who is console
	{
		  doomcom.consoleplayer = atoi(myargv[i+1])-1;
	}
	else
	{
		 doomcom.consoleplayer = console;
	}
	 doomcom.numplayers = total;

	 printf (STR_CONSOLEIS"\n", console+1, total);
}


//========================================================
//
//	Find a Response File
//
//========================================================
void FindResponseFile (void)
{
	int		i;
	#define	MAXARGVS	100

	for (i = 1;i < myargc;i++)
		if (myargv[i][0] == '@')
		{
			FILE *		handle;
			int		size;
			int		k;
			int		index;
			int		indexinfile;
			char	*infile;
			char	*file;
			char	*moreargs[20];
			char	*firstargv;

			// READ THE RESPONSE FILE INTO MEMORY
			handle = fopen (&myargv[i][1],"rb");
			if (!handle)
				Error (STR_NORESP);
			printf(STR_FOUNDRESP" \"%s\"!\n",strupr(&myargv[i][1]));
			fseek (handle,0,SEEK_END);
			size = ftell(handle);
			fseek (handle,0,SEEK_SET);
			file = malloc (size);
			fread (file,size,1,handle);
			fclose (handle);

			// KEEP ALL CMDLINE ARGS FOLLOWING @RESPONSEFILE ARG
			for (index = 0,k = i+1; k < myargc; k++)
				moreargs[index++] = myargv[k];

			firstargv = myargv[0];
			myargv = malloc(sizeof(char *)*MAXARGVS);
			memset(myargv,0,sizeof(char *)*MAXARGVS);
			myargv[0] = firstargv;

			infile = file;
			indexinfile = k = 0;
			indexinfile++;	// SKIP PAST ARGV[0] (KEEP IT)
			do
			{
				myargv[indexinfile++] = infile+k;
				while(k < size &&
					((*(infile+k)>= ' '+1) && (*(infile+k)<='z')))
					k++;
				*(infile+k) = 0;
				while(k < size &&
					((*(infile+k)<= ' ') || (*(infile+k)>'z')))
					k++;
			} while(k < size);

			for (k = 0;k < index;k++)
				myargv[indexinfile++] = moreargs[k];
			myargc = indexinfile;

			// DISPLAY ARGS
//			printf("%d command-line args:\n",myargc);
//			for (k=1;k<myargc;k++)
//				printf("%s\n",myargv[k]);

			break;
		}
}


/*
=============
=
= main
=
=============
*/

void main (void)
{
	int  i;
	unsigned char far *vector;

	//
	// determine game parameters
	//
	gameid = 0;
	numnetnodes = 2;
	doomcom.ticdup = 1;
	if((i = CheckParm("-dup")) != 0)
		doomcom.ticdup = atoi(myargv[i+1]);
	if((i = CheckParm("-ticdup")) != 0)
		doomcom.ticdup = atoi(myargv[i+1]);
	doomcom.extratics = 1;
	doomcom.episode = 1;
	doomcom.map = 1;
	doomcom.skill = 2;
	doomcom.deathmatch = 0;

	printf("\n");
	#ifdef DOOM2
	printf(STR_DOOMNETDRV"\n");
	#else
	#ifdef HERETIC
	printf("Universal Network Device Driver v1.22a\n");
	#else
	printf("Universal Network Device Driver v1.22a\n");
	#endif
	#endif

	myargc = _argc;
	myargv = _argv;

	if (CheckParm("-?") || CheckParm("/?"))
	{
		printf("\nCommand-line parameters:\n");
		printf("-nodes <#> = specify # of players (default = 2 players).\n");
		printf("-vector <#> = specify a different interrupt vector (hexadecimal value).\n");
		printf("-port <#> = specify a different network socket (default = 0x869c).\n");
		printf("-exe <exename.exe> = specify a custom game executable to launch.\n");
		printf("-player <#> = specify which node number you want to be.\n");
		printf("\nAny additional parameters will be passed on to the game executable.\n");
		exit(1);
	}

	FindResponseFile();

	if((i = CheckParm("-nodes")) != 0)
		numnetnodes = atoi(myargv[i+1]);

	if((i = CheckParm("-vector")) != 0)
	{
		doomcom.intnum = sscanf ("0x%x",myargv[i+1]);
		vector = *(char far * far *)(doomcom.intnum*4);
		if(vector != NULL && *vector != 0xcf)
		{
			printf(STR_VECTSPEC"\n", doomcom.intnum);
			exit(-1);
		}
	}
	else
	{
		for(doomcom.intnum = 0x60 ; doomcom.intnum <= 0x66 ; doomcom.intnum++)
		{
			vector = *(char far * far *)(doomcom.intnum*4);
			if(vector == NULL || *vector == 0xcf)
				break;
		}
		if(doomcom.intnum == 0x67)
		{
			printf(STR_NONULL"\n");
			exit(-1);
		}
	}
	printf(STR_COMMVECT"\n",doomcom.intnum);

	if((i = CheckParm("-port")) != 0)
	{
		socketid = atoi (myargv[i+1]);
		printf (STR_USEALT"\n", socketid);
	}

	InitNetwork ();

	LookForNodes ();

	localtime = 0;

	LaunchDOOM ();

	ShutdownNetwork ();

	if (vectorishooked)
		setvect (doomcom.intnum,olddoomvect);

	exit(0);
}


