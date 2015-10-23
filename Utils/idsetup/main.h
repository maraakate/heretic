//
// MAIN.H
//
#include "setup.h"
#include "menu.h"
#include "keys.h"

// In the Project Manager, change the DEFINES for the EXE
// for the different versions of SETUP. Valid #defines are:
// DOOM			// define if for DOOM
// DOOM2			// define if for DOOM II
// HERETIC		// define if for HERETIC
// FRENCH		// define if FRENCH VERSION (any game)

#ifdef DOOM2
#define	EXENAME	"DOOMNEW.EXE"
#define	DEFAULTNAME	"DEFAULT.CFG"
#define	DEFAULTPATH	"C:\\DOOMDATA"
#define	SAVENAME		"DOOMSAV%d.DSG"
#endif

#ifdef DOOM
#define	EXENAME	"DOOMNEW.EXE"
#define	DEFAULTNAME	"DEFAULT.CFG"
#define	DEFAULTPATH	"C:\\DOOMDATA"
#define	SAVENAME		"DOOMSAV%d.DSG"
#endif

#ifdef HERETIC
#define	HTICSHADOW // FS: For Shadow of the Serpent Riders (Removes WARP Menu)
#define	EXENAME	"HERETIC.EXE"
#define	DEFAULTNAME	"HERETIC.CFG"
#define	DEFAULTPATH	"C:\\HERETIC.CD"
#define SAVENAME                "HTICSAV%d.HSG"
#endif

#ifdef HEXEN
#define	EXENAME	"HEXEN.EXE"
#define	DEFAULTNAME	"HEXEN.CFG"
#define	DEFAULTPATH	"C:\\HEXEN.CD"
#define	SAVENAME		"HEXNDATA\\HEX%d.HXS"
#endif

#ifdef FRENCH

#define S_NONE "AUCUNE"
#define S_PCSP "Haut-parleur PC"
#define S_CON1 "Clavier seul"
#define S_CON2 "Clavier + Souris"
#define S_CON3 "Clavier + Joystick"

#else

#define S_NONE "None"
#define S_PCSP "PC Speaker"
#define S_CON1 "Keyboard only"
#define S_CON2 "Keyboard + Mouse"
#define S_CON3 "Keyboard + Joystick"

#endif

#define MAXARGS   12

typedef enum { FALSE, TRUE }	BOOL;

typedef enum
{
   M_NONE,
   M_PC,
   M_ADLIB,
   M_SB,
   M_PAS,
   M_GUS,
   M_WAVE,
   M_CANVAS,
   M_GMIDI,
   M_SBAWE32,
   M_LAST
}SCARD;
  
typedef enum
{
   C_KEY,
   C_MOUSE,
   C_JOYSTICK,
   C_LAST
}CONTROL;

typedef struct
{
	SCARD card;
   short port;
   short midiport;
   short irq;
   short dma;
} DMXCARD;

typedef struct
{
   CONTROL control;
   DMXCARD m;
   DMXCARD d;
   short numdig;
} DMXINFO;

typedef struct
{
   int   numberOfPlayers;
   int   skillLevel;
   int   deathMatch;
   unsigned  networkSocket;
   int   episode;
} net_t;

typedef struct
{
	int   skillLevel;
	int   deathMatch;
	int   episode;
	int   comport;
	int   comtype;  // 0 = connected,1 = answer,2 = call
	char  phonenum[16];
} serial_t;

typedef struct
{
	int      up;
	int      down;
	int      left;
	int      right;
	int      fire;
	int      use;     // ID = USE         CYGNUS = USE SPECIAL WEAPON
	int      key1;    // ID = STRAFE ON   CYGNUS = CHANGE SPECIAL WEAPON
	int      key2;    // ID = SPEED ON    CYGNUS = MEGA BOMB HOT KEY
	int      key3;    // ID = STRAFE LEFT
	int      key4;    // ID = STRAFE RIGHT
#ifdef HERETIC
	int		lookdown;
	int		lookcenter;
	int		lookup;
	int		flydown;
	int		flycenter;
	int		flyup;
	int		invleft;
	int		invright;
#endif
#ifdef HEXEN
	int		lookdown;
	int		lookcenter;
	int		lookup;
	int		flydown;
	int		flycenter;
	int		flyup;
	int		invleft;
	int		invright;
#endif

#ifdef HEXEN
	int		jump;

	int      mouse[5];
#else
	int	mouse[3];
#endif

	int      joy[4];
} CONTS;

typedef enum
{
	ID_FIRE,        // def button 1
	ID_STRAFE,      // def button 3
	ID_FORWARD,     // def button 2
	ID_USE,          // def button 4 joystick only
#ifdef HEXEN
	ID_JUMP,		// FS: For Hexen
#endif
}IDCONTS;

extern int  usemouse;
extern int  usejoystick;
extern int	comport;

typedef struct
{
	char  name[64];
	char  init[64];
	char  hangup[64];
	char  baud[8];
} modem_t;

#define MAXMODEMS 200

typedef struct
{
	char  name[32];
	char  number[16];
} phonelist_t;

#define MAXPHNLIST 40

extern	char	keydesc[256][10];
extern	int	cdrom;
extern	int	respawn;
extern	int	nomonsters;
extern	int	mousepresent;
extern	DMXINFO lastc;
extern	DMXINFO newc;
extern	BOOL    savemusic;
extern	BOOL    savefx;
extern	CONTS  curk;

//
// Network macros
//
extern char  chatmacros[10][40];

extern	net_t netinfo;
extern	net_t info;     	// in case ESC is pressed

extern	serial_t modeminfo;
extern	serial_t minfo;   // in case ESC is pressed

extern	serial_t serialinfo;
extern	serial_t sinfo;   // in case ESC is pressed

void	ErrorWindow(pup_t far *pup);
void	StartUp(void);
void	MainMenu (void);
void	DrawCurrentConfig(void);
int   QuitAndSave(void);

//
// Functions in other modules
//

// MUSIC.C
int	SetupMusic(void);
int	ChooseSbPort (DMXCARD * card);
int	ChooseMidiPort (DMXCARD * card);

// WARP.C
extern	int   respawn;
extern	int   nomonsters;
extern	int   deathmatch2;
unsigned WarpTime(void);

// SFX.C
int	SetupFX(void);

// CONTROL.C
int ChooseController(void);

// CONFIG.C
void ConfigControl (void);
void Pos(item_t *item);
void Clear(item_t *item);

// NETPLAY.C
void ChooseNetplay(void);
void AttriBar(int x,int y,int length, char attr);

// MACROS.C
void MacroConfig(void);
int	EditLine(item_t *item,char *string,int maxlen);

// MODEM.C
int ModemConfig(void);
int ChooseOpponentInList(void);
extern char  chosenPhoneNum[16];

// SERIAL.C
int SerialConfig(void);

// NET.C
int NetworkConfig(void);

// NETREST.C
extern char  savenames[6][24];
extern int   saveslot;
int RestoreNetwork(void);
void ChooseNetrestore(void);

// MODREST.C
int RestoreModem(void);

// SERREST.C
int RestoreSerial(void);

