//#define	DEBUG			// shows all windows
extern void Error (char *error, ...);

typedef	unsigned char byte;

typedef struct
{
	int	x;    	// xcoord of radio
	int	y;			// ycoord of radio
	int	value;	// value to match
} radio_t;

typedef struct
{
	radio_t *radios;	// start of radio buttons
	int	amount;		// # of radio buttons
	int	*master;		// master value that radios must match
	int	fgcolor;		// text color
	int	bgcolor;		// background color
} radiogroup_t;

typedef	struct
{
	short	pup_id;
	char	width;
	char	height;
	char	x;
	char	y;
	short	mystery1;
	short	mystery2;
} pup_t;

typedef enum
{
	normal,
	stringdraw,
	repeat
} pup_e;

#define MAXLAYERS		1	// max amount of screens to save
void SaveScreen(void);
void RestoreScreen(void);
void DrawRadios(radiogroup_t *rg);

void DrawPup(pup_t far *pup);
#ifdef DEBUG
void ShowAllPups(void);
#endif
extern char errorstring[80];
//void Error(char *string);
