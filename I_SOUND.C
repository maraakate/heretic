#include <stdio.h>
#include <stdlib.h>

#include "doomdef.h"
#include "dmx.h"
#include "sounds.h"
#include "i_sound.h"
#include "i_system.h"
#include "GUS.H" /* FS: For internal HT_GUS1M.WAD */

boolean hasGUS = false; /* FS */
/* FS: Use internal GUS1M WAD */
extern int useIntGus;
extern char *htgus;

int tsm_ID = -1;

void I_StartupTimer (void)
{
#ifndef NOTIMER
	extern int I_TimerISR(void);

	tprintf("I_StartupTimer()\n",0);
	/* installs master timer.	Must be done before StartupTimer()! */
	TSM_Install(SND_TICRATE);
	tsm_ID = TSM_NewService (I_TimerISR, 35, 255, 0); /* max priority */
	if (tsm_ID == -1)
	{
		I_Error("Can't register 35 Hz timer w/ DMX library");
	}
#endif
}

void I_ShutdownTimer (void)
{
	TSM_DelService(tsm_ID);
	TSM_Remove();
}

/* sound information */
#if 0
const char *dnames[] = {"None",
			"PC_Speaker",
			"Adlib",
			"Sound_Blaster",
			"ProAudio_Spectrum16",
			"Gravis_Ultrasound",
			"MPU",
			"AWE32"
			};
#endif

const char snd_prefixen[] = { 'P', 'P', 'A', 'S', 'S', 'S', 'M', 'M', 'M', 'S' };

int snd_Channels;
int snd_DesiredMusicDevice, snd_DesiredSfxDevice;
int snd_MusicDevice,		/* current music card # (index to dmxCodes) */
	snd_SfxDevice,			/* current sfx card # (index to dmxCodes) */
	snd_MaxVolume,			/* maximum volume for sound */
	snd_MusicVolume;		/* maximum volume for music */
int dmxCodes[NUM_SCARDS]; /* the dmx code for a given card */

int snd_SBport, snd_SBirq, snd_SBdma;	/* sound blaster variables */
int snd_Mport;							/* midi variables */

extern boolean	snd_MusicAvail, /* whether music is available */
		snd_SfxAvail;			/* whether sfx are available */

void I_PauseSong (int handle)
{
	MUS_PauseSong(handle);
}

void I_ResumeSong (int handle)
{
	MUS_ResumeSong(handle);
}

void I_SetMusicVolume (int volume)
{
	MUS_SetMasterVolume(volume*8);
//	snd_MusicVolume = volume;
}

void I_SetSfxVolume (int volume)
{
	snd_MaxVolume = volume; /* THROW AWAY? */
}

int I_RegisterSong (void *data)
{
	int rc = MUS_RegisterSong(data);
#ifdef SNDDEBUG
	if (rc<0)
		printf("MUS_Reg() returned %d\n", rc);
#endif
	return rc;
}

void I_UnRegisterSong (int handle)
{
	int rc = MUS_UnregisterSong(handle);
#ifdef SNDDEBUG
	if (rc < 0)
		printf("MUS_Unreg() returned %d\n", rc);
#endif
}

int I_QrySongPlaying (int handle)
{
	int rc = MUS_QrySongPlaying(handle);
#ifdef SNDDEBUG
	if (rc < 0)
		printf("MUS_QrySP() returned %d\n", rc);
#endif
	return rc;
}

void I_StopSong (int handle) /* MUST be called before I_UnregisterSong(). */
{
	int rc, s;
	extern volatile int ticcount;

	rc = MUS_StopSong(handle);
#ifdef SNDDEBUG
	if (rc < 0)
		printf("MUS_StopSong() returned %d\n", rc);
#endif

	/* Fucking kluge pause */
	for (s=ticcount; ticcount - s < 10; );
}

void I_PlaySong (int handle, boolean looping)
{
	int rc;

	rc = MUS_ChainSong(handle, looping ? handle : -1);
#ifdef SNDDEBUG
	if (rc < 0)
		printf("MUS_ChainSong() returned %d\n", rc);
#endif

	rc = MUS_PlaySong(handle, snd_MusicVolume);
#ifdef SNDDEBUG
	if (rc < 0)
		printf("MUS_PlaySong() returned %d\n", rc);
#endif

}

/* Gets lump nums of the named sound.	Returns pointer which will be
 * passed to I_StartSound() when you want to start an SFX.	Must be
 * sure to pass this to UngetSoundEffect() so that they can be
 * freed!
 */
int I_GetSfxLumpNum (sfxinfo_t *sound)
{
	char namebuf[9];

	if(sound->name == 0)
		return 0;
	if (sound->link)
		sound = sound->link;
	return W_GetNumForName(sound->name);

}

int I_StartSound (int id, void *data, int vol, int sep, int pitch, int priority)
{
	return SFX_PlayPatch(data, pitch, sep, vol, 0, 0);

}

void I_StopSound (int handle)
{
	SFX_StopPatch(handle);
}

int I_SoundIsPlaying (int handle)
{
	return SFX_Playing(handle);
}

void I_UpdateSoundParams (int handle, int vol, int sep, int pitch)
{
	SFX_SetOrigin(handle, pitch, sep, vol);
}

/* Why PC's Suck, Reason #8712 */
void I_sndArbitrateCards (void)
{
	char tmp[160];
	boolean gus, adlib, pc, sb, midi;
	int i, rc, mputype, p, opltype, wait, dmxlump, retval;

	// snd_MaxVolume = 127;
	// Damn you, Dave Taylor!

	snd_MusicDevice = snd_DesiredMusicDevice;
	snd_SfxDevice = snd_DesiredSfxDevice;

	/* check command-line parameters- overrides config file */
	if (M_CheckParm("-nosound"))
		snd_MusicDevice = snd_SfxDevice = snd_none;
	if (M_CheckParm("-nosfx"))
		snd_SfxDevice = snd_none;
	if (M_CheckParm("-nomusic"))
		snd_MusicDevice = snd_none;

	if (M_CheckParm("-usesb")) /* FS: Force SB if you're using a GUS combo */
	{
		snd_MusicDevice = snd_SfxDevice = snd_SB;
		snd_SBport = 0x220;
		snd_SBirq = 5;
		snd_SBdma = 1;
		printf("	Forcing SB detection at A%03xh I%d D%d.\n", snd_SBport, snd_SBirq, snd_SBdma);
	}

	if (snd_MusicDevice > snd_MPU && snd_MusicDevice <= snd_MPU3)
		snd_MusicDevice = snd_MPU;
	if (snd_MusicDevice == snd_SB)
		snd_MusicDevice = snd_Adlib;
	if (snd_MusicDevice == snd_PAS)
		snd_MusicDevice = snd_Adlib;

	/* figure out what i've got to initialize */
	gus = snd_MusicDevice == snd_GUS || snd_SfxDevice == snd_GUS;
	sb = snd_SfxDevice == snd_SB || snd_MusicDevice == snd_SB;
	adlib = snd_MusicDevice == snd_Adlib ;
	pc = snd_SfxDevice == snd_PC;
	midi = snd_MusicDevice == snd_MPU;

	/* initialize whatever i've got */
	if (gus)
	{
		byte *gusbuffer; /* FS: Use an external GUS ini file */
		int	gusfilelength, p;

		retval = GF1_Detect();
		if (retval)
		{
			sprintf(tmp, "Dude.	The GUS ain't responding retval=%d.\n", retval);
			tprintf(tmp, 1);
		}
		else
		{
			hasGUS = true;
			tprintf("SB_Init: Loading GUS patches.\n", 1);
			hgotoxy(17,9);
			hprintf("Loading GUS patches.", 0x3f);

			p = M_CheckParm("-usegusini"); /* FS: Use an external GUS ini file */
			if (p)
			{
				if(p < myargc-1)
				{
					char *gusfile = myargv[p+1];
					gusfilelength = M_ReadFile(gusfile, &gusbuffer);
					GF1_SetMap((char *)gusbuffer, gusfilelength);
					Z_Free(gusbuffer);
				}
				else
				{
					I_ShutdownKeyboard();
					printf("ERROR: No external GUS file specified! Use -usegusini <filename.ini>.\n");
					exit(1);
				}
			}
			else
			{
				if (M_CheckParm("-gus") || useIntGus)
				{
					int length = strlen(htgus);
					tprintf("	using internal HT_GUS1M.WAD\n", 1);
					GF1_SetMap(htgus, length);
				}
				else
				{
					dmxlump = W_GetNumForName("dmxgus");
					GF1_SetMap(W_CacheLumpNum(dmxlump, PU_CACHE), lumpinfo[dmxlump].size);
				}
			}
		}
	}

	if (sb)
	{
		if(debugmode)
		{
			sprintf(tmp,"cfg p=%03xh, i=%d, d=%d\n", snd_SBport, snd_SBirq, snd_SBdma);
			tprintf(tmp,0);
		}

		retval = SB_Detect(&snd_SBport, &snd_SBirq, &snd_SBdma, 0);
		if (retval)
		{
			sprintf(tmp,"SB isn't responding at p=%03xh, i=%d, d=%d, retval=%d\n", snd_SBport, snd_SBirq, snd_SBdma, retval);
			tprintf(tmp,0);
		}
		else
		{
			SB_SetCard(snd_SBport, snd_SBirq, snd_SBdma);
		}

		if(debugmode)
		{
			sprintf(tmp,"SB_Detect returned p=%03xh,i=%d,d=%d,retval=%d\n",	snd_SBport, snd_SBirq, snd_SBdma, retval);
			tprintf(tmp,0);
		}
	}

	if (adlib)
	{
		retval = AL_Detect(&wait,0);
		if (retval)
		{
			sprintf(tmp, "Dude.	The Adlib isn't responding retval=%d.\n", retval);
			tprintf(tmp,1);
		}
		else
		{
			AL_SetCard(wait, W_CacheLumpName("genmidi", PU_STATIC));
		}
	}

	if (midi)
	{
		if (debugmode)
		{
			sprintf(tmp,"cfg p=%03xh\n", snd_Mport);
			tprintf(tmp,0);
		}

		retval = MPU_Detect(&snd_Mport, &i);
		if (retval)
		{
			sprintf(tmp,"The MPU-401 isn't reponding @ p=%03xh, retval=%d.\n", snd_Mport, retval);
			tprintf(tmp,0);
		}
		else
		{
			MPU_SetCard(snd_Mport);
		}
	}

}

void I_StartupSound (void)
{
	char tmp[80];
	int rc, i;

	if (debugmode)
		tprintf("I_StartupSound: Hope you hear a pop.\n",1);

	dmxCodes[0] = 0;
	dmxCodes[snd_PC] = AHW_PC_SPEAKER;
	dmxCodes[snd_Adlib] = AHW_ADLIB;
	dmxCodes[snd_SB] = AHW_SOUND_BLASTER;
	dmxCodes[snd_PAS] = AHW_MEDIA_VISION;
	dmxCodes[snd_GUS] = AHW_ULTRA_SOUND;
	dmxCodes[snd_MPU] = AHW_MPU_401;
	dmxCodes[snd_AWE] = AHW_AWE32;

	/* inits sound library timer stuff */
	I_StartupTimer();

	/* pick the sound cards i'm going to use */
	I_sndArbitrateCards();

	if (debugmode)
	{
		sprintf(tmp,"	Music device #%d & dmxCode=%d\n", snd_MusicDevice, dmxCodes[snd_MusicDevice]);
		tprintf(tmp,0);
		sprintf(tmp,"	Sfx device #%d & dmxCode=%d\n", snd_SfxDevice, dmxCodes[snd_SfxDevice]);
		tprintf(tmp,0);
	}

	tprintf("	calling DMX_Init\n",0);
	rc = DMX_Init(SND_TICRATE, SND_MAXSONGS, dmxCodes[snd_MusicDevice],
	dmxCodes[snd_SfxDevice]);

	if (debugmode)
	{
		sprintf(tmp,"	DMX_Init() returned %d\n", rc);
		tprintf(tmp,0);
	}

}

void I_ShutdownSound (void)
{
	DMX_DeInit();
	I_ShutdownTimer();
}

void I_SetChannels (int channels)
{
	if (M_CheckParm("-s8"))
		WAV_PlayMode(channels, 8000);
	else if (M_CheckParm("-s11"))
		WAV_PlayMode(channels, 11025);
	else if (M_CheckParm("-s22"))
		WAV_PlayMode(channels, 22050);
	else
		WAV_PlayMode(channels, SND_SAMPLERATE);
}
