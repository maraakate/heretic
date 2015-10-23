//
// Configure controllers
//
#include <dos.h>
#include <conio.h>
#include <bios.h>

#include "main.h"

void Pos(item_t *item)
{
	gotoxy(item->x+1,item->y+1);
}

void Clear(item_t *item)
{
	int	i;

	Pos(item);
	for (i = 0;i < item->w; i++)
		cprintf(" ");
	gotoxy(1,25);
}

//
//	Get keyboard scan code
//
int GetScanCode (void)
{
	volatile unsigned short  rval;

	while (kbhit())
		getch();

	SaveScreen();
	DrawPup(&askpres);

	while(1)
	{
		rval = _bios_keybrd ( _KEYBRD_SHIFTSTATUS );

		if ( rval & 0x0004 )
		{
			rval = SC_CTRL;
			break;
		}
		else if ( rval & 0x0008 )
		{
			rval = SC_ALT;
			break;
		}
		else if ( rval & 0x0001 )
		{
			rval = SC_RIGHT_SHIFT;
			break;
		}
		else
		{
			rval = _bios_keybrd ( _KEYBRD_READY );
			rval = rval >> 8;

			if ( rval == SC_ENTER ) rval = 0;
			if ( rval == SC_BACKSPACE ) rval = 0;

			if ( rval ) break;
		}
	}

	RestoreScreen();
	while (kbhit())
		getch();

	return ( rval );
}

enum {FORWARD,BACKWARD,LEFT,RIGHT,
#ifdef HEXEN
	JUMP,
#endif
#if defined(HERETIC) || defined(HEXEN)
		LOOKD,LOOKC,LOOKU,FLYD,FLYC,FLYU,
#endif
		USE,FIRE,SPEED,STRAFE,STRAFE_LEFT,STRAFE_RIGHT,
#if defined(HERETIC) || defined(HEXEN)
		INVL,INVR,
#endif
		MAXKEYS};
item_t idkeyselitems[]=
{
#if defined(HERETIC) || defined(HEXEN)

#ifdef HEXEN
	{FORWARD,		39,5,5, 	-1,JUMP},
#else
	{FORWARD,		39,5,8, 	-1,-1},
#endif

	{BACKWARD,		39,6,8, 	-1,-1},
	{LEFT,			39,7,8, 	-1,-1},
#ifdef HEXEN
	{RIGHT,			39,8,8, 	-1,-1,LEFT,LOOKD},
#else
	{RIGHT,			39,8,8, 	-1,-1},
#endif

#ifdef HEXEN
	{JUMP,			50,5,5,	FORWARD,-1,INVR},
#endif

	{LOOKD,			29,10,8,	-1,LOOKC,	RIGHT,FLYD},
	{LOOKC,			39,10,8,	LOOKD,LOOKU,	RIGHT,FLYC},
	{LOOKU,			49,10,8,	LOOKC,-1,	RIGHT,FLYU},

	{FLYD,			29,11,8,	-1,FLYC,	LOOKD,USE},
	{FLYC,			39,11,8,	FLYD,FLYU,	LOOKC,USE},
	{FLYU,			49,11,8,	FLYC,-1,	LOOKU,SPEED},

	{USE,				29,13,8,	-1,SPEED,	FLYD},
	{FIRE,			29,14,8,	-1,STRAFE},
	{SPEED,			49,13,8,	USE,-1,	FLYU},
	{STRAFE,			49,14,8,	FIRE,-1},
	{STRAFE_LEFT,	42,15,8,	-1,-1,	FIRE},
	{STRAFE_RIGHT,	42,16,8,	-1,-1},

	{INVL,			42,17,8, -1,-1},

#ifdef HEXEN
	{INVR,			42,18,8,	-1,-1,INVL,JUMP}
#else
	{INVR,			42,18,8,	-1,-1}
#endif

#else
	{FORWARD,		47,5,8, 	-1,-1},
	{BACKWARD,		47,6,8, 	-1,-1},
	{LEFT,			47,7,8, 	-1,-1},
	{RIGHT,			47,8,8,	-1,-1},

	{USE,				47,12,8,	-1,-1},
	{FIRE,			47,13,8,	-1,-1},
	{SPEED,			47,14,8,	-1,-1},
	{STRAFE,			47,15,8,	-1,-1},
	{STRAFE_LEFT,	47,16,8,	-1,-1},
	{STRAFE_RIGHT,	47,17,8,	-1,-1},
#endif
};
menu_t idkeyselmenu=
{
	&idkeyselitems[0],
	FORWARD,
	MAXKEYS,
	0x7f
};

void IDConfigKeyboard(void)
{
	short field;
	short	key;
	CONTS	turk;
	int   rval;

	SaveScreen();
	DrawPup(&idkeysel);

	turk = curk;

	textbackground(1);
	textcolor(15);
	Clear(&idkeyselitems[FORWARD]);
	Pos(&idkeyselitems[FORWARD]);
	cprintf("%s",keydesc[turk.up] );
	Clear(&idkeyselitems[BACKWARD]);
	Pos(&idkeyselitems[BACKWARD]);
	cprintf("%s",keydesc[turk.down] );
	Clear(&idkeyselitems[LEFT]);
	Pos(&idkeyselitems[LEFT]);
	cprintf("%s",keydesc[turk.left] );
	Clear(&idkeyselitems[RIGHT]);
	Pos(&idkeyselitems[RIGHT]);
	cprintf("%s",keydesc[turk.right] );
	Clear(&idkeyselitems[USE]);
	Pos(&idkeyselitems[USE]);
	cprintf("%s",keydesc[turk.use] );
	Clear(&idkeyselitems[FIRE]);
	Pos(&idkeyselitems[FIRE]);
	cprintf("%s",keydesc[turk.fire] );
	Clear(&idkeyselitems[SPEED]);
	Pos(&idkeyselitems[SPEED]);
	cprintf("%s",keydesc[turk.key2] );
	Clear(&idkeyselitems[STRAFE]);
	Pos(&idkeyselitems[STRAFE]);
	cprintf("%s",keydesc[turk.key1] );
	Clear(&idkeyselitems[STRAFE_LEFT]);
	Pos(&idkeyselitems[STRAFE_LEFT]);
	cprintf("%s",keydesc[turk.key3] );
	Clear(&idkeyselitems[STRAFE_RIGHT]);
	Pos(&idkeyselitems[STRAFE_RIGHT]);
	cprintf("%s",keydesc[turk.key4] );

#if defined(HERETIC) || defined(HEXEN)
	Clear(&idkeyselitems[LOOKD]);
	Pos(&idkeyselitems[LOOKD]);
	cprintf("%s",keydesc[turk.lookdown] );
	Clear(&idkeyselitems[LOOKC]);
	Pos(&idkeyselitems[LOOKC]);
	cprintf("%s",keydesc[turk.lookcenter] );
	Clear(&idkeyselitems[LOOKU]);
	Pos(&idkeyselitems[LOOKU]);
	cprintf("%s",keydesc[turk.lookup] );
#ifdef HEXEN
	Pos(&idkeyselitems[JUMP]);
	cprintf("%s",keydesc[turk.jump]);
#endif
	Clear(&idkeyselitems[FLYD]);
	Pos(&idkeyselitems[FLYD]);
	cprintf("%s",keydesc[turk.flydown] );
	Clear(&idkeyselitems[FLYC]);
	Pos(&idkeyselitems[FLYC]);
	cprintf("%s",keydesc[turk.flycenter] );
	Clear(&idkeyselitems[FLYU]);
	Pos(&idkeyselitems[FLYU]);
	cprintf("%s",keydesc[turk.flyup] );

	Clear(&idkeyselitems[INVL]);
	Pos(&idkeyselitems[INVL]);
	cprintf("%s",keydesc[turk.invleft] );
	Clear(&idkeyselitems[INVR]);
	Pos(&idkeyselitems[INVR]);
	cprintf("%s",keydesc[turk.invright] );
#endif

	gotoxy(1,25);

	while(1)
	{
		SetupMenu(&idkeyselmenu);
		field = GetMenuInput();
		key = menukey;
		switch ( key )
		{
			case KEY_ESC:
					goto func_exit;

			case KEY_F10:
					curk = turk;
					goto func_exit;

			case KEY_ENTER:
				switch ( field )
				{
					case FORWARD:
						rval = GetScanCode();
						if ( rval )
						{
							turk.up = rval;
							Clear(&idkeyselitems[FORWARD]);
							Pos(&idkeyselitems[FORWARD]);
							cprintf("%s",keydesc[turk.up] );
						}
						break;

					case BACKWARD:
						rval = GetScanCode();
						if ( rval )
						{
							turk.down = rval;
							Clear(&idkeyselitems[BACKWARD]);
							Pos(&idkeyselitems[BACKWARD]);
							cprintf("%s",keydesc[turk.down] );
						}
						break;

					case LEFT:
						rval = GetScanCode();
						if ( rval )
						{
							turk.left = rval;
							Clear(&idkeyselitems[LEFT]);
							Pos(&idkeyselitems[LEFT]);
							cprintf("%s",keydesc[turk.left] );
						}
						break;

					case RIGHT:
						rval = GetScanCode();
						if ( rval )
						{
							turk.right = rval;
							Clear(&idkeyselitems[RIGHT]);
							Pos(&idkeyselitems[RIGHT]);
							cprintf("%s",keydesc[turk.right] );
						}
						break;

					case USE:
						rval = GetScanCode();
						if ( rval )
						{
							turk.use = rval;
							Clear(&idkeyselitems[USE]);
							Pos(&idkeyselitems[USE]);
							cprintf("%s",keydesc[turk.use] );
						}
						break;

					case FIRE:
						rval = GetScanCode();
						if ( rval )
						{
							turk.fire = rval;
							Clear(&idkeyselitems[FIRE]);
							Pos(&idkeyselitems[FIRE]);
							cprintf("%s",keydesc[turk.fire] );
						}
						break;

					case SPEED:
						rval = GetScanCode();
						if ( rval )
						{
							turk.key2 = rval;
							Clear(&idkeyselitems[SPEED]);
							Pos(&idkeyselitems[SPEED]);
							cprintf("%s",keydesc[turk.key2] );
						}
						break;

					case STRAFE:
						rval = GetScanCode();
						if ( rval )
						{
							turk.key1 = rval;
							Clear(&idkeyselitems[STRAFE]);
							Pos(&idkeyselitems[STRAFE]);
							cprintf("%s",keydesc[turk.key1] );
						}
						break;

					case STRAFE_LEFT:
						rval = GetScanCode();
						if ( rval )
						{
							turk.key3 = rval;
							Clear(&idkeyselitems[STRAFE_LEFT]);
							Pos(&idkeyselitems[STRAFE_LEFT]);
							cprintf("%s",keydesc[turk.key3] );
						}
						break;

					case STRAFE_RIGHT:
						rval = GetScanCode();
						if ( rval )
						{
							turk.key4 = rval;
							Clear(&idkeyselitems[STRAFE_RIGHT]);
							Pos(&idkeyselitems[STRAFE_RIGHT]);
							cprintf("%s",keydesc[turk.key4] );
						}
						break;

					#if defined(HERETIC) || defined(HEXEN)
					#ifdef HEXEN
					case JUMP:
						rval = GetScanCode();
						if ( rval )
						{
							turk.jump = rval;
							Clear(&idkeyselitems[JUMP]);
							Pos(&idkeyselitems[JUMP]);
							cprintf("%s",keydesc[turk.jump] );
						}
						break;
					#endif
					case LOOKD:
						rval = GetScanCode();
						if ( rval )
						{
							turk.lookdown = rval;
							Clear(&idkeyselitems[LOOKD]);
							Pos(&idkeyselitems[LOOKD]);
							cprintf("%s",keydesc[turk.lookdown] );
						}
						break;
					case LOOKC:
						rval = GetScanCode();
						if ( rval )
						{
							turk.lookcenter = rval;
							Clear(&idkeyselitems[LOOKC]);
							Pos(&idkeyselitems[LOOKC]);
							cprintf("%s",keydesc[turk.lookcenter] );
						}
						break;
					case LOOKU:
						rval = GetScanCode();
						if ( rval )
						{
							turk.lookup = rval;
							Clear(&idkeyselitems[LOOKU]);
							Pos(&idkeyselitems[LOOKU]);
							cprintf("%s",keydesc[turk.lookup] );
						}
						break;

					case FLYD:
						rval = GetScanCode();
						if ( rval )
						{
							turk.flydown = rval;
							Clear(&idkeyselitems[FLYD]);
							Pos(&idkeyselitems[FLYD]);
							cprintf("%s",keydesc[turk.flydown] );
						}
						break;
					case FLYC:
						rval = GetScanCode();
						if ( rval )
						{
							turk.flycenter = rval;
							Clear(&idkeyselitems[FLYC]);
							Pos(&idkeyselitems[FLYC]);
							cprintf("%s",keydesc[turk.flycenter] );
						}
						break;
					case FLYU:
						rval = GetScanCode();
						if ( rval )
						{
							turk.flyup = rval;
							Clear(&idkeyselitems[FLYU]);
							Pos(&idkeyselitems[FLYU]);
							cprintf("%s",keydesc[turk.flyup] );
						}
						break;

					case INVL:
						rval = GetScanCode();
						if ( rval )
						{
							turk.invleft = rval;
							Clear(&idkeyselitems[INVL]);
							Pos(&idkeyselitems[INVL]);
							cprintf("%s",keydesc[turk.invleft] );
						}
						break;
					case INVR:
						rval = GetScanCode();
						if ( rval )
						{
							turk.invright = rval;
							Clear(&idkeyselitems[INVR]);
							Pos(&idkeyselitems[INVR]);
							cprintf("%s",keydesc[turk.invright] );
						}
						break;
					#endif
				}
				gotoxy(1,25);
				break;
		}
	}

	func_exit:

	RestoreScreen();
	return;
}

//
//	Configure joystick buttons
//
enum
{
	J_FIRE,
	J_FORWARD,
	J_USE,
	J_STRAFE,
	J_MAX
};
item_t idjoyselitems[]=
{
	{J_FIRE,		42,10,9,	-1,-1},
	{J_FORWARD,	42,11,9,	-1,-1},
	{J_USE,		42,12,9,	-1,-1},
	{J_STRAFE,	42,13,9,	-1,-1}
};
menu_t idjoyselmenu=
{
	&idjoyselitems[0],
	J_FIRE,
	J_MAX,
	0x7f
};

//
//	Get joystick button
//
int GetJoyButton (void)
{
	int      rval     = -1;
	int      num;
	int      c;

	SaveScreen();
	DrawPup(&mousentr);

	while(kbhit())
		getch();

	while(1)
	{
		num = inp ( 0x201 );

		num = num >> 4;

		if ( ! ( num & 1 ) )
		{
			rval = 0;
			break;
		}
		if ( ! ( num & 2 ) )
		{
			rval = 1;
			break;
		}
		if ( ! ( num & 4 ) )
		{
			rval = 2;
			break;
		}
		if ( ! ( num & 8 ) )
		{
			rval = 3;
			break;
		}

		if (kbhit())
		{
			c=_bios_keybrd( _KEYBRD_READY ) >> 8;
			if (c == SC_ESC)
				break;

			getch();
		}
//      if ( ( _bios_keybrd ( _KEYBRD_READY ) >> 8 ) == SC_ESC ) break;

	}

	RestoreScreen();
	while(kbhit())
		getch();

	return ( rval );
}

void IDConfigJoy (void)
{
	short		key;
	short		field;
	int		rval;
	CONTS 	turk;
	char		joybuts [4][20] =
	{
		"BUTTON 1",
		"BUTTON 2",
		"BUTTON 3",
		"BUTTON 4"
	};
	int		fire;
	int		frwd;
	int		strf;
	int		use;

	SaveScreen();
	DrawPup(&idjoysel);

	turk = curk;

	fire = turk.joy[ ID_FIRE ];
	frwd = turk.joy[ ID_FORWARD ];
	strf = turk.joy[ ID_STRAFE ];
	use  = turk.joy[ ID_USE ];

	textbackground(1);
	textcolor(15);
	Clear(&idjoyselitems[J_FIRE]);
	Pos(&idjoyselitems[J_FIRE]);
	if (fire >= 0)
		cprintf("%s",joybuts[fire]);

	Clear(&idjoyselitems[J_FORWARD]);
	Pos(&idjoyselitems[J_FORWARD]);
	if (frwd >= 0)
		cprintf("%s",joybuts[ frwd ] );

	Clear(&idjoyselitems[J_STRAFE]);
	Pos(&idjoyselitems[J_STRAFE]);
	if (strf >= 0)
		cprintf("%s",joybuts[ strf ] );

	Clear(&idjoyselitems[J_USE]);
	Pos(&idjoyselitems[J_USE]);
	if (use >= 0)
		cprintf("%s",joybuts[ use ] );
	gotoxy(1,25);

   while(1)
	{
		SetupMenu(&idjoyselmenu);
		field = GetMenuInput();
		key = menukey;
		switch ( key )
		{
			case KEY_ESC:
               goto func_exit;

			case KEY_F10:
					curk = turk;
					goto func_exit;

			case KEY_ENTER:
				switch ( field )
				{
					case J_FIRE:
						rval = GetJoyButton();
						if ( rval != -1 )
						{
							turk.joy [ ID_FIRE ] = rval;
							Clear(&idjoyselitems[J_FIRE]);
							Pos(&idjoyselitems[J_FIRE]);
							cprintf("%s",joybuts[ rval ] );

							if (turk.joy [ ID_FORWARD ] == rval)
							{
								turk.joy [ ID_FORWARD ] = -1;
								Clear(&idjoyselitems[J_FORWARD]);
							}
							if (turk.joy [ ID_USE ] == rval)
							{
								turk.joy [ ID_USE ] = -1;
								Clear(&idjoyselitems[J_USE]);
							}
							if (turk.joy [ ID_STRAFE ] == rval)
							{
								turk.joy [ ID_STRAFE ] = -1;
								Clear(&idjoyselitems[J_STRAFE]);
							}
						}
						break;

					case J_FORWARD:
						rval = GetJoyButton();
                  if ( rval != -1 )
                  {
                     turk.joy [ ID_FORWARD ] = rval;
							Clear(&idjoyselitems[J_FORWARD]);
							Pos(&idjoyselitems[J_FORWARD]);
							cprintf("%s",joybuts[rval]);

							if (turk.joy [ ID_FIRE ] == rval)
							{
								turk.joy [ ID_FIRE ] = -1;
								Clear(&idjoyselitems[J_FIRE]);
							}
							if (turk.joy [ ID_USE ] == rval)
							{
								turk.joy [ ID_USE ] = -1;
								Clear(&idjoyselitems[J_USE]);
							}
							if (turk.joy [ ID_STRAFE ] == rval)
							{
								turk.joy [ ID_STRAFE ] = -1;
								Clear(&idjoyselitems[J_STRAFE]);
							}
                  }
						break;

					case J_USE:
						rval = GetJoyButton();
						if ( rval != -1 )
						{
							turk.joy [ ID_USE ] = rval;
							Clear(&idjoyselitems[J_USE]);
							Pos(&idjoyselitems[J_USE]);
							cprintf("%s",joybuts[rval]);

							if (turk.joy [ ID_FORWARD ] == rval)
							{
								turk.joy [ ID_FORWARD ] = -1;
								Clear(&idjoyselitems[J_FORWARD]);
							}
							if (turk.joy [ ID_FIRE ] == rval)
							{
								turk.joy [ ID_FIRE ] = -1;
								Clear(&idjoyselitems[J_FIRE]);
							}
							if (turk.joy [ ID_STRAFE ] == rval)
							{
								turk.joy [ ID_STRAFE ] = -1;
								Clear(&idjoyselitems[J_STRAFE]);
							}
						}
						break;

					case J_STRAFE:
						rval = GetJoyButton();
						if ( rval != -1 )
						{
							turk.joy [ ID_STRAFE ] = rval;
							Clear(&idjoyselitems[J_STRAFE]);
							Pos(&idjoyselitems[J_STRAFE]);
							cprintf("%s",joybuts[rval]);

							if (turk.joy [ ID_FORWARD ] == rval)
							{
								turk.joy [ ID_FORWARD ] = -1;
								Clear(&idjoyselitems[J_FORWARD]);
							}
							if (turk.joy [ ID_USE ] == rval)
							{
								turk.joy [ ID_USE ] = -1;
								Clear(&idjoyselitems[J_USE]);
							}
							if (turk.joy [ ID_FIRE ] == rval)
							{
								turk.joy [ ID_FIRE ] = -1;
								Clear(&idjoyselitems[J_FIRE]);
							}
						}
						break;
				}
				gotoxy(1,25);
				break;
		}
	}

	func_exit:

	RestoreScreen();
	return;
}

//
// Configure mouse buttons
//
#ifdef HEXEN
	enum {M_FIRE,M_FORWARD,M_STRAFE,M_JUMP,M_MAX};
#else
	enum {M_FIRE,M_FORWARD,M_STRAFE,M_MAX};
#endif

item_t idmouselitems[]=
{
	{M_FIRE,		44,9,13,		-1,-1},
	{M_FORWARD,	44,10,13,	-1,-1},
#ifdef HEXEN
	{M_STRAFE,	44,11,13,	-1,-1},
	{M_JUMP,	44,12,13,	-1,-1}
#else
	{M_STRAFE,	44,11,13,	-1,-1}
#endif
};
menu_t idmouselmenu=
{
	&idmouselitems[0],
	M_FIRE,
	M_MAX,
	0x7f
};

//
//	Get mouse button
//
int GetMouseButton (void)
{
	int      rval = -1;
	union    REGS r;

	SaveScreen();
	DrawPup(&mousentr);

	while(1)
	{
		r.x.ax = 3;
		int86 ( 0x33, &r, &r );

		if ( r.x.bx & 1 )
			rval = 0;
		else if ( r.x.bx & 2 )
			rval = 1;
		else if ( r.x.bx & 4 )
			rval = 2;

		if ( rval != -1 ) break;

		if ( ( _bios_keybrd ( _KEYBRD_READY ) >> 8 ) == SC_ESC ) break;
	}

	RestoreScreen();
	while(kbhit())
		getch();

	return ( rval );
}

void IDConfigMouse (void)
{
	short		key;
	short		field;
	int		rval;
	CONTS		turk;
	char mousebuts [3][20] = {
		"LEFT BUTTON",
		"RIGHT BUTTON",
		"MID BUTTON"
	};
	int   fire;
	int   frwd;
	int   strf;
#ifdef HEXEN
	int jump;
#endif

	SaveScreen();
	DrawPup(&idmousel);
	turk = curk;

	fire = turk.mouse[ ID_FIRE ];
	frwd = turk.mouse[ ID_FORWARD ];
	strf = turk.mouse[ ID_STRAFE ];
#ifdef HEXEN
	jump = turk.mouse[ ID_JUMP ];
#endif

	textbackground(1);
	textcolor(15);
	Clear(&idmouselitems[M_FIRE]);
	Pos(&idmouselitems[M_FIRE]);
	if (fire >= 0)
		cprintf("%s",mousebuts[ fire ] );

	Clear(&idmouselitems[M_FORWARD]);
	Pos(&idmouselitems[M_FORWARD]);
	if (frwd >= 0)
		cprintf("%s",mousebuts[ frwd ] );

	Clear(&idmouselitems[M_STRAFE]);
	Pos(&idmouselitems[M_STRAFE]);
	if (strf >= 0)
		cprintf("%s",mousebuts[ strf ] );

#ifdef HEXEN
	Clear(&idmouselitems[M_JUMP]);
	Pos(&idmouselitems[M_JUMP]);
	if (jump >= 0)
		cprintf("%s",mousebuts[ jump ] );
#endif
	gotoxy(1,25);

	while(1)
	{
		SetupMenu(&idmouselmenu);
		field = GetMenuInput();
		key = menukey;
		switch ( key )
		{
			case KEY_ESC:
					goto func_exit;

			case KEY_F10:
					curk = turk;
					goto func_exit;

			case KEY_ENTER:
				switch ( field )
				{
					case M_FIRE:
						rval = GetMouseButton();
						if ( rval != -1 )
						{
							turk.mouse [ ID_FIRE ] = rval;
							Clear(&idmouselitems[M_FIRE]);
							Pos(&idmouselitems[M_FIRE]);
							cprintf("%s",mousebuts [ rval ] );
							if (turk.mouse [ ID_STRAFE ] == rval)
							{
								turk.mouse [ ID_STRAFE ] = -1;
								Clear(&idmouselitems[M_STRAFE]);
							}
							if (turk.mouse [ ID_FORWARD ] == rval)
							{
								turk.mouse [ ID_FORWARD ] = -1;
								Clear(&idmouselitems[M_FORWARD]);
							}
#ifdef HEXEN
							if (turk.mouse [ ID_JUMP ] == rval)
							{
								turk.mouse [ ID_JUMP ] = -1;
								Clear(&idmouselitems[M_JUMP]);
							}
#endif
						}
						break;

					case M_FORWARD:
						rval = GetMouseButton();
						if ( rval != -1 )
						{
							turk.mouse [ ID_FORWARD ] = rval;
							Clear(&idmouselitems[M_FORWARD]);
							Pos(&idmouselitems[M_FORWARD]);
							cprintf("%s",mousebuts [ rval ] );

							if (turk.mouse [ ID_STRAFE ] == rval)
							{
								turk.mouse [ ID_STRAFE ] = -1;
								Clear(&idmouselitems[M_STRAFE]);
							}
							if (turk.mouse [ ID_FIRE ] == rval)
							{
								turk.mouse [ ID_FIRE ] = -1;
								Clear(&idmouselitems[M_FIRE]);
							}
#ifdef HEXEN
							if (turk.mouse [ ID_JUMP ] == rval)
							{
								turk.mouse [ ID_JUMP ] = -1;
								Clear(&idmouselitems[M_JUMP]);
							}
#endif
						}
						break;

					case M_STRAFE:
						rval = GetMouseButton();
						if ( rval != -1 )
						{
							turk.mouse [ ID_STRAFE ] = rval;
							Clear(&idmouselitems[M_STRAFE]);
							Pos(&idmouselitems[M_STRAFE]);
							cprintf("%s",mousebuts[rval]);

							if (turk.mouse [ ID_FORWARD ] == rval)
							{
								turk.mouse [ ID_FORWARD ] = -1;
								Clear(&idmouselitems[M_FORWARD]);
							}
							if (turk.mouse [ ID_FIRE ] == rval)
							{
								turk.mouse [ ID_FIRE ] = -1;
								Clear(&idmouselitems[M_FIRE]);
							}
#ifdef HEXEN
							if (turk.mouse [ ID_JUMP ] == rval)
							{
								turk.mouse [ ID_JUMP ] = -1;
								Clear(&idmouselitems[M_JUMP]);
							}
#endif
						}
						break;
#ifdef HEXEN
					case M_JUMP:
						rval = GetMouseButton();
						if ( rval != -1 )
						{
							turk.mouse [ ID_JUMP ] = rval;
							Clear(&idmouselitems[M_JUMP]);
							Pos(&idmouselitems[M_JUMP]);
							cprintf("%s",mousebuts[rval]);

							if (turk.mouse [ ID_FORWARD ] == rval)
							{
								turk.mouse [ ID_FORWARD ] = -1;
								Clear(&idmouselitems[M_FORWARD]);
							}
							if (turk.mouse [ ID_FIRE ] == rval)
							{
								turk.mouse [ ID_FIRE ] = -1;
								Clear(&idmouselitems[M_FIRE]);
							}
							if (turk.mouse [ ID_STRAFE ] == rval)
							{
								turk.mouse [ ID_STRAFE ] = -1;
								Clear(&idmouselitems[M_STRAFE]);
							}
						}
						break;
#endif
				}
				gotoxy(1,25);
				break;
		}
	}

	func_exit:

	RestoreScreen();
	return;
}

//
// Choose which controller to configure!
//
enum {CFG_KEY,CFG_MOUSE,CFG_JOY,CFG_MAX};
item_t conselitems[]=
{
	{CFG_KEY,	31,11,14,	-1,-1},
	{CFG_MOUSE,	31,12,14,	-1,-1},
	{CFG_JOY,	31,13,14,	-1,-1}
};
menu_t conselmenu=
{
	&conselitems[0],
	CFG_KEY,
	CFG_MAX,
	0x7f
};

void ConfigControl (void)
{
	short   key;
	short   field;

	SaveScreen();
	DrawPup(&consel);

	while(1)
	{
		SetupMenu(&conselmenu);
		field = GetMenuInput();
		key = menukey;

		if ( key == KEY_ESC )
			break;

		if ( key != KEY_ENTER && key != KEY_F10 ) continue;

		switch ( field )
		{
			default:
			case CFG_KEY:
				IDConfigKeyboard();
				goto func_exit;

			case CFG_MOUSE:
				if ( !mousepresent )
				{
					ErrorWindow(&mouspres);
					break;
				}
				IDConfigMouse();
				goto func_exit;

			case CFG_JOY:
				IDConfigJoy();
				goto func_exit;
		}
	}

	func_exit:

	RestoreScreen();
	return;
}
