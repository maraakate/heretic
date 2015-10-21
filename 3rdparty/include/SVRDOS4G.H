#ifndef _SVRDOS_H_
#define _SVRDOS_H_

// Header file for SVRDOS32
// SimulEyes VR driver for DOS 32-bit extenders.

/*
 *-----------------------------------------------------------
 * Definitions for all the necessary data types and macros
 *-----------------------------------------------------------
 */
#ifndef NULL
#define NULL                0
#endif

#ifndef FALSE
#define FALSE               0
#endif

#ifndef TRUE
#define TRUE                1
#endif

#ifndef FAR
#define FAR                 far
#endif

#ifndef NEAR
#define NEAR                near
#endif

#ifndef VOID
#define VOID                void
#endif

#ifndef BOOL
typedef int                 BOOL;
#endif

#ifndef BYTE
typedef unsigned char       BYTE;
#endif

#ifndef WORD
typedef unsigned short      WORD;
#endif

#ifndef DWORD
typedef unsigned long       DWORD;
#endif

#ifndef PBYTE
typedef unsigned char *     PBYTE;
#endif

#ifndef LPBYTE
typedef unsigned char far * LPBYTE;
#endif

/*
 *-------------------------------------------------------
 * data structure definitions
 *-------------------------------------------------------
 */

#define SVRDOS_VERSION      0x0200

// function result code definitions
#define	SVR_OK		1
#define	SVR_ERROR	0

// video mode definitions for SVRDOS32
// (may be different from definitions for SVRDOS)
#define SVR_320_200         0x13
#define SVR_320_200_X       0x14
#define SVR_TEXT            0x03
#define SVR_ORIGINAL        0xFFFF
#define SVR_PREVIOUS        0xFFFE

// left/right stereo buffer definitions
#define	LEFT	0
#define	RIGHT	1

// identifying information structure for SVRDOS32
typedef struct SVRDosInfo {
    DWORD       hardware_version;   // hardware version
    DWORD       driver_version;     // driver version
    DWORD       video_mode;         // graphics mode
} SVRDosInfo_t;

// options data structure for SVRDOS32 run-time service routine
typedef struct SVRDosOption {
    DWORD	calls_far;      // SVR function calls near or far ?
    DWORD	pixels_modex;   // pixel data ordering linear or mode-X ?
    DWORD	pixels_width;   // pixel data width gaps in pixel buffer ?
    DWORD	debug_port;     // use port for debugging ISR activity ?
    DWORD       pal_protect;    // protect palette during video mode set ?
    DWORD	line_alternate; // pixel data linear or line-alternate ?
    DWORD	high_refresh;   // standard video refresh rate or higher ?
    DWORD	lock_flip;      // SVR ISR polls for vertical retrace ?
    DWORD	delay_flip;     // SVR ISR flip delay after vertical retrace
    DWORD	fast_intr;      // SVR ISR interrupt rate doubler
    DWORD       OEM_support;	// support special OEM chipset
} SVRDosOption_t;

/*
 *-----------------------------------------------------------
 * External procedure definitions
 *-----------------------------------------------------------
 */

int SVRDosInit (void);
int SVRDosExit (void);
int SVRDosSetMode (WORD mode);
int SVRDosGetMode (void);
int SVRDosGetInfo (SVRDosInfo_t FAR * lpInfo);
int SVRDosSetImage (BOOL eye, WORD x0, WORD y0, WORD xd, WORD yd, LPBYTE buf);
int SVRDosGetImage (BOOL eye, WORD x0, WORD y0, WORD xd, WORD yd, LPBYTE buf);
int SVRDosGetRegistration (void);
int SVRDosSetRegistration (BOOL active);
int SVRDosSetBlackCode (BYTE color);
int SVRDosSetWhiteCode (BYTE color);
int SVRDosSync (void);
int SVRDosSetOptions (SVRDosOption_t FAR * lpOptions);
int SVRDosGetOptions (SVRDosOption_t FAR * lpOptions);

#endif
