#ifndef __I_SOUND_H
#define __I_SOUND_H

#include "sounds.h"

#define SND_TICRATE		140             // tic rate for updating sound
#define SND_MAXSONGS	40              // max number of songs in game
#define SND_SAMPLERATE	11025   // sample rate of sound effects

typedef enum
{
	snd_none,	// P
	snd_PC,		// P
	snd_Adlib,	// A
	snd_SB,		// S
	snd_PAS,	// S
	snd_GUS,	// S
	snd_MPU,	// M
	snd_MPU2,	// M
	snd_MPU3,	// M
	snd_AWE,	// S
	NUM_SCARDS
} cardenum_t;

void I_StartupSound (void);
void I_ShutdownSound (void);

void I_SetChannels(int channels);
void I_SetMusicVolume(int volume);
int I_GetSfxLumpNum(sfxinfo_t *sound);

int I_StartSound (int id, void *data, int vol, int sep, int pitch, int priority);
void I_StopSound(int handle);

int I_SoundIsPlaying(int handle);
void I_UpdateSoundParams(int handle, int vol, int sep, int pitch);

int I_RegisterSong(void *data);
void I_PlaySong(int handle, boolean looping);
void I_PauseSong(int handle);
void I_ResumeSong(int handle);
void I_StopSong(int handle);
void I_UnRegisterSong(int handle);

#endif // __I_SOUND_H
