#ifndef __S_SOUND__
#define __S_SOUND__

#include "doomdef.h"
#include "doomdata.h"

#ifdef __GNUG__
#pragma interface
#endif

//
// Initializes sound stuff, including volume
// Sets channels, SFX and music volume,
//  allocates channel buffer, sets S_sfx lookup.
//
void S_Init (void);

//
// Per level startup code.
// Kills playing sounds at start of level,
//  determines music if any, changes music.
//
void S_Start(void);

//
// Start sound for thing at <origin>
//  using <sound_id> from sounds.h
//
void S_StartSound(mobj_t *origin, int sound_id);

// Will start a sound at a given volume.
void S_StartSoundAtVolume(mobj_t *origin, int sound_id, int volume);

// Stop sound for thing at <origin>
void S_StopSound(mobj_t *origin);

// Start music using <music_id> from sounds.h
void S_StartSong(int song, boolean loop);

// Stop and resume music, during game PAUSE.
void S_PauseSound(void);
void S_ResumeSound(void);

//
// Updates music & sounds
//
void S_UpdateSounds(mobj_t *listener);

void S_SetMusicVolume(void);
void S_SetSfxVolume(void);

void S_FreeChannels (void);
void S_ShutDown(void);

boolean S_StopSoundID(int sound_id, int priority);
void S_SetMaxVolume(boolean fullprocess);

#endif
