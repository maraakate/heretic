#ifndef __I_SYSTEM_H
#define __I_SYSTEM_H

#include "doomdef.h"

void DPMIInt (int i);

void I_InitVRGoggles (void);
void I_ShutdownVRGoggles (boolean exit);

void I_StartupKeyboard (void);
void I_ShutdownKeyboard (void);
void I_StartupJoystick (void);
void I_CheckExternDriver(void);
void I_JoystickEvents (void);

//--------
//SOUND IO
//--------
#define	FREQ_LOW		0x40
#define FREQ_NORM		0x80
#define FREQ_HIGH		0xff

void I_SetMasterVolume(int volume);

void I_TurnOffSfx(void);
void I_TurnOnSfx(void);
void I_TurnOffMusic(void);
void I_TurnOnMusic(void);

//  MUSIC I/O
//

int I_RegisterSong(void *songdata);
// called by anything that wants to register a song lump with the sound lib
// calls Paul's function of the similar name to register music only.
// note that the song data is the same for any sound card and is paul's
// MUS format.  Returns a handle which will be passed to all other music
// functions.

void I_UnregisterSong(int handle);
// called by anything which is finished with a song and no longer needs
// the sound library to be aware of it.  All songs should be stopped
// before calling this, but it will double check and stop it if necessary.

void I_LoopSong(int handle);
// called by anything that wishes to start music.
// plays a song, and when the song is done, starts playing it again in
// an endless loop.  the start is faded in over three seconds.

void I_FadeOutSong(int handle, int fotime);
// called by anything that wishes to stop music.
// fades out the song over <fotime> milliseconds.

void I_StopSong(int handle);
// called by anything that wishes to stop music.
// stops a song abruptly.

//  SFX I/O
//

void *I_GetSoundEffect (char *soundname);
// called by routines which wish to play a sound effect at some later
// time.  Pass it the lump name of a sound effect WITHOUT the sfx
// prefix.  This means the maximum name length is 7 letters/digits.
// The prefixes for different sound cards are 'S','M','A', and 'P'.
// They refer to the card type.  The routine will cache in the
// appropriate sound effect when it is played.

void I_UngetSoundEffect (void *soundset);
// called by routines which wish to no longer use the sounds at all
// frees up the associated structure.  It stops any currently playing
// sound effects.

int I_StartSound (int id, void *data, int vol, int sep, int pitch, int priority);
// Starts a sound in a particular sound channel

void I_UpdateSoundParams(int handle, int vol, int sep, int pitch);
// Updates the volume, separation, and pitch of a sound channel

void I_StopSound(int handle);
// Stops a sound channel

int I_SoundIsPlaying(int handle);
// called by S_*()'s to see if a channel is still playing.  Returns 0
// if no longer playing, 1 if playing.

/* FS: Missing prototypes */
void I_PlaySong(int handle, boolean looping);
int I_GetSfxLumpNum(sfxinfo_t *sound);
void I_PauseSong(int handle);
void I_ResumeSong(int handle);
void I_StartupSound (void);
void I_SetChannels(int channels);
void I_SetMusicVolume(int volume);
void I_ShutdownSound (void);
void I_UnRegisterSong(int handle);

#endif // __I_SYSTEM_H
