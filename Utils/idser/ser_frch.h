#ifdef DOOM2
#define EXENAME	"DOOM2.EXE"
#else
#ifdef HERETIC
#define EXENAME	"HERETIC.EXE"
#else
#define EXENAME	"DOOM.EXE"
#endif
#endif

#define STR_DROPDTR		"Abandon de DTR"
#define STR_CLEANEXIT	"Sortie normale de SERSETUP"
#define STR_ATTEMPT		"Tentative de connexion en s�rie, appuyez sur ESC pour annuler."
#define STR_NETABORT	"Synchronisation de jeu sur r�seau annul�e."
#define STR_DUPLICATE	"Cha�ne id en double. R�essayez ou v�rifiez la cha�ne d'initialistion du modem."
#define STR_MODEMCMD	"Commande du modem: "
#define STR_MODEMRESP	"R�ponse du modem: "
#define STR_RESPABORT	"R�ponse du modem annul�e."
#define STR_CANTREAD	"Lecture de MODEM.CFG impossible"
#define STR_DIALING		"Composition du num�ro..."
#define STR_CONNECT		"CONNECTION"
#define STR_WAITRING	"Attente d'appel..."
#define STR_RING		"APPEL"
#define STR_NORESP		"Ce fichier de r�ponse n'existe pas!"
#define STR_DOOMSERIAL	"GESTIONNAIRE DE LIAISON SERIE DOOM II v1.4"
#define STR_WARNING \
"Attention: pas de vecteurs d'interruption NULL ou iret trouv�s entre 0x60 et 0x66.\n"\
"Vous pouvez sp�cifier un vecteur avec le param�tre -vector 0x<num�ro>."
#define STR_COMM		"Communication avec le vecteur d'interruption 0x%x"
#define STR_RETURNED	"Retour de "EXENAME
#define STR_PORTSET		"R�glage du port � %lu baud"
#define STR_PORTLOOK	"Recherche de l'UART sur le port"
#define STR_UART8250	"UART = 8250"
#define STR_UART16550	"UART = 16550"
#define STR_CLEARPEND	"Riinitilisation des interruptions en attente.\n"

