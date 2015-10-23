//
// Save & Load defaults
//
#include <dir.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <io.h>
#include <bios.h>

#include "default.h"
#include "keys.h"
#include "main.h"

int		usemouse;
int		usejoystick;

extern   net_t   netinfo;
extern   DMXINFO newc;
extern   CONTS   curk;

int	mouseSensitivity  = 4;
int	showMessages      = 1;
int	sfxVolume         = 15;
int	musicVolume       = 15;
int	detailLevel       = 1;
int	screenblocks      = 10;
int   usegamma          = 0;

#if 0
	int	usePalFlash		= 1; // FS
	int	headBob		= 1; // FS
	int drawTime	= 0; // FS
	int	grmode		= 1; // FS

	// FS: Custom weapon keys
	int	use_wpnbinds = 0;
	int	wpn_shotgun;
	int	wpn_crossbow; 
	int	wpn_chaingun;
	int	wpn_dragon;
	int	wpn_rocket;
	int	wpn_phoenix;
	int	wpn_plasma;
	int	wpn_hellstaff;
#endif

int	comport		= 1;

char  chatmacros[10][40];

default_t	defaults[] =
{
	{"mouse_sensitivity",&mouseSensitivity, 5},
	{"sfx_volume",&sfxVolume, 8},
	{"music_volume",&musicVolume, 8},
	{"show_messages",&showMessages, 1},

	{"key_right",&curk.right, SC_RIGHT },
	{"key_left",&curk.left, SC_LEFT },
	{"key_up",&curk.up, 17 }, // FS: SC_UP
	{"key_down",&curk.down, 31 }, // FS: SC_DOWN
	{"key_strafeleft",&curk.key3, 30 }, // FS: SC_COMMA
	{"key_straferight",&curk.key4, 32 }, // FS: SC_PERIOD
	{"key_fire",&curk.fire, SC_CTRL },
	{"key_use",&curk.use, 18 }, // FS: SC_SPACE
	{"key_strafe",&curk.key1, SC_ALT },
	{"key_speed",&curk.key2, SC_RIGHT_SHIFT },
#if defined(HERETIC) || defined(HEXEN)
	{"key_flydown",&curk.flydown,SC_INSERT},
	{"key_flycenter",&curk.flycenter,SC_HOME},
	{"key_flyup",&curk.flyup,SC_PAGEUP},
	{"key_lookdown",&curk.lookdown,SC_DELETE},
	{"key_lookcenter",&curk.lookcenter,SC_END},
	{"key_lookup",&curk.lookup,SC_PAGEDN},
	{"key_invleft",&curk.invleft,0x1a},
	{"key_invright",&curk.invright,0x1b},
#endif
#ifdef HEXEN
	{"key_jump", &curk.jump, SC_SPACE }, // FS: 0x35
#endif

#if 0
	{"usePalFlash",&usePalFlash, 1}, // FS
	{"headBob",&headBob, 1}, // FS
	{"drawTime",&drawTime, 0}, // FS

	// FS: Use custom weapon binds
	{ "use_wpnbinds", &use_wpnbinds, 0},
#if defined(DOOM) || defined(DOOM2)
	{ "wpn_shotgun", &wpn_shotgun, 44 }, // FS: Z
	{ "wpn_chaingun", &wpn_chaingun, 45 }, // FS: X
	{ "wpn_rocket", &wpn_rocket, 16 }, // FS: Q
	{ "wpn_plasma", &wpn_plasma, 46 }, // FS: C
	{ "disk_flash_icon", &grmode, 1 }, // FS: Disk Flashing Icon
#endif // DOOM || DOOM2

#ifdef HERETIC
	{ "wpn_crossbow", &wpn_crossbow, 44 }, // FS: Z
	{ "wpn_dragon", &wpn_dragon, 45 }, // FS: X
	{ "wpn_phoenix", &wpn_phoenix, 16 }, // FS: Q
	{ "wpn_hellstaff", &wpn_hellstaff, 46 }, // FS: C
#endif // HERETIC
#endif // 0

	{"use_mouse",&usemouse, 1 },
	{"mouseb_fire",&curk.mouse[ID_FIRE],ID_FIRE },
	{"mouseb_strafe",&curk.mouse[ID_STRAFE],ID_STRAFE },
	{"mouseb_forward",&curk.mouse[ID_FORWARD],ID_FORWARD },

#ifdef HEXEN
	{"mouseb_jump",&curk.mouse[ID_JUMP], -1},
#endif

	{"use_joystick",&usejoystick, 0},
	{"joyb_fire",&curk.joy[ID_FIRE],ID_FIRE},
	{"joyb_strafe",&curk.joy[ID_STRAFE],ID_STRAFE},
	{"joyb_use",&curk.joy[ID_USE],ID_USE},
	{"joyb_speed",&curk.joy[ID_FORWARD],ID_FORWARD},

	{"screenblocks",&screenblocks, 9},
	{"detaillevel",&detailLevel, 0},
	{"showmessages",&showMessages, 1 },
	{"comport",&comport, 1 },

	{"snd_channels", (int *)&newc.numdig, 3 },

	{"snd_musicdevice", (int *)&newc.m.card, 0 },
	{"snd_sfxdevice", (int *)&newc.d.card, 0 },
	{"snd_sbport", (int *)&newc.m.port, 0x220 },
	{"snd_sbirq", (int *)&newc.d.irq, 5 },
	{"snd_sbdma", (int *)&newc.d.dma, 1 },
	{"snd_mport", (int *)&newc.m.midiport, 0x330 },

	{"usegamma", &usegamma, 0 },

	{"chatmacro0",(int *)chatmacros[0],0},
	{"chatmacro1",(int *)chatmacros[1],0},
	{"chatmacro2",(int *)chatmacros[2],0},
	{"chatmacro3",(int *)chatmacros[3],0},
	{"chatmacro4",(int *)chatmacros[4],0},
	{"chatmacro5",(int *)chatmacros[5],0},
	{"chatmacro6",(int *)chatmacros[6],0},
	{"chatmacro7",(int *)chatmacros[7],0},
	{"chatmacro8",(int *)chatmacros[8],0},
	{"chatmacro9",(int *)chatmacros[9],0},

	{"",NULL,0},

};

int		numdefaults;
char	*  defaultfile;

/*
==============
=
= M_SaveDefaults
=
==============
*/

void M_SaveDefaults (void)
{
	int		i;
	FILE	*  f;

	if ( newc.m.port == -1 )
	{
		if ( newc.d.port == -1 )
			newc.m.port = 0x220;
		else
			newc.m.port = newc.d.port;
	}

	if ( newc.control != C_KEY )
	{
		if ( newc.control == C_MOUSE )
			usemouse = 1;

		if ( newc.control == C_JOYSTICK )
         usejoystick = 1;
   }

   numdefaults = sizeof(defaults)/sizeof(default_t);

   f = fopen (defaultfile, "w");
	if (!f)
      return;			// can't write the file, but don't complain

   for (i=0 ; i<numdefaults ; i++)
      if (!strncmp(defaults[i].name,"chatmacro",9))
      {
         int v = defaults[i].name[9] - '0';
         fprintf (f,"%s\t\t\"%s\"\n",defaults[i].name, chatmacros[v]);
      }
      else
         fprintf (f,"%s\t\t%i\n",defaults[i].name, *defaults[i].location);

	fclose (f);
}

int CheckParm(char *string)
{
   int   i;

	for (i = 1;i < myargc;i++)
		if (!strcmp(myargv[i],string))
			return i;
	return 0;
}

char *defaultchatmacro[10] =	// FS: Use the defaults instead of having "no macro"
{
	"I'm ready to kick butt!",
	"I'm OK.",
	"I'm not looking too good!",
	"Help!",
	"You suck!",
	"Next time, scumbag...",
	"Come here!",
	"I'll take care of it.",
	"Yes",
	"No"
};

/*
==============
=
= M_LoadDefaults
=
==============
*/
int M_LoadDefaults (void)
{
	int		i;
	FILE		*f;
	char		def[80];
	char		strparm[50];
	int		parm;
	char		macro[40];

//
// set everything to base values
//
	numdefaults = sizeof(defaults)/sizeof(defaults[0]);
	for (i=0 ; i<numdefaults ; i++)
		if ( !strncmp(defaults[i].name,"chatmacro",9) )
		{
			char *chatnum = strchr(defaults[i].name, 'o');
			int z = chatnum[1]-48; // FS: Because I don't know how to atoi this properly.

			strcpy((char *)defaults[i].location,defaultchatmacro[z]);
		}
		else
			*defaults[i].location = defaults[i].defaultvalue;

	cdrom = 0;
	if (CheckParm("-cdrom"))
	{
		mkdir(DEFAULTPATH);
		defaultfile = DEFAULTPATH"\\"DEFAULTNAME;
		cdrom = 1;
	}
	else
		defaultfile = DEFAULTNAME;                 // hard-coded path GONE!

	i = CheckParm("-config");
	if (i)
		defaultfile = myargv[i+1];

//
// read the file in, overriding any set defaults
//
	f = fopen (defaultfile, "r");
	if (!f)
		return(0);			// no overrides
		
	while (!feof(f))
	{
		fscanf ( f, "%79s %[^\n]", def, strparm );
		
      macro[0] = 0;
      if (!strncmp(def,"chatmacro",9))
         sscanf(strparm+1,"%[^\"]",macro);
      else
      if (strparm[0] == '0' && strparm[1] == 'x')
		  sscanf(strparm+2, "%x", &parm);
      else
		  sscanf(strparm, "%i", &parm);

      for (i=0 ; i<numdefaults ; i++)
			if (!strcmp(def, defaults[i].name) )
			{
            if (!strncmp(def,"chatmacro",9))
               strcpy((char *)defaults[i].location,macro);
            else
				   *defaults[i].location = parm;
				break;
			}
	}
	
	fclose (f);

   newc.d.port = newc.m.port;

   if ( usemouse )
      newc.control = C_MOUSE;
   else if ( usejoystick )
      newc.control = C_JOYSTICK;
   else
      newc.control = C_KEY;

   return(1);
}

