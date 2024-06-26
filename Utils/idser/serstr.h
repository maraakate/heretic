#ifdef DOOM2
#define EXENAME	"DOOM2.EXE"
#else
#ifdef HERETIC
#define EXENAME	"HERETIC.EXE"
#else
#define EXENAME	"DOOM.EXE"
#endif
#endif

#define STR_DROPDTR		"Dropping DTR"
#define STR_CLEANEXIT	"Clean exit from SERSETUP"
#define STR_ATTEMPT		"Attempting to connect across serial link, press escape to abort."
#define STR_NETABORT	"Network game synchronization aborted."
#define STR_DUPLICATE	"Duplicate id string, try again or check modem init string."
#define STR_MODEMCMD	"Modem command : "
#define STR_MODEMRESP	"Modem response: "
#define STR_RESPABORT	"Modem response aborted."
#define STR_CANTREAD	"Couldn't read MODEM.CFG"
#define STR_DIALING		"Dialing..."
#define STR_CONNECT		"CONNECT"
#define STR_WAITRING	"Waiting for ring..."
#define STR_RING		"RING"
#define STR_NORESP		"No such response file!"
#define STR_DOOMSERIAL	"DOOM II SERIAL DEVICE DRIVER v1.4"
#define STR_WARNING \
"Warning: no NULL or iret interrupt vectors were found in the 0x60 to 0x66\n"\
"range.  You can specify a vector with the -vector 0x<num> parameter.\n"
#define STR_COMM		"Communicating with interrupt vector 0x%x"
#define STR_RETURNED	"Returned from "EXENAME
#define STR_PORTSET		"Setting port to %lu baud"
#define STR_PORTLOOK	"Looking for UART at port"
#define STR_UART8250	"UART is an 8250"
#define STR_UART16550	"UART is a 16550"
#define STR_CLEARPEND	"Clearing pending interrupts.\n"

