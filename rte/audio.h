/*============*\
| AUDIO HEADER |
\*============*/

#ifndef _AUDIO_H_
#define _AUDIO_H_

Uint32 xyLoadSound(const char* filename);
Uint32 xyLoadMusic(const char* filename);
void xyDeleteSound(Uint32 sound);
void xyDeleteMusic(Uint32 music);
int xyPlaySound(Uint32 sound, Uint32 loops);
int xyPlayMusic(Uint32 music, Uint32 loops);


#endif
