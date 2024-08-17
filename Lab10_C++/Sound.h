// Sound.h
// Runs on TM4C123 or LM4F120
// Prototypes for basic functions to play sounds from the
// original Space Invaders.
// Jonathan Valvano
// November 17, 2014
#ifndef __SOUND_H__ // do not include more than once
#define __SOUND_H__
#include <stdint.h>
typedef enum {Sound_Begin, Sound_Chomp, Sound_Death} SoundName;
void Sound_Off(void);
void SetSound(SoundName i);
void Sound_Init(void);
void SoundOut(void);
bool notFinished();
void endSound();
#endif


