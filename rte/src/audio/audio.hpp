//  Brux - Audio Portability API
//  Copyright (C) 2016 KelvinShadewing
//  Copyright (C) 2023 hexaheximal
//
//  This program is free software: you can redistribute it and/or modify
//  it under the terms of the GNU Affero General Public License as published by
//  the Free Software Foundation, either version 3 of the License, or
//  (at your option) any later version.
//
//  This program is distributed in the hope that it will be useful,
//  but WITHOUT ANY WARRANTY; without even the implied warranty of
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//  GNU Affero General Public License for more details.
//
//  You should have received a copy of the GNU Affero General Public License
//  along with this program.  If not, see <http://www.gnu.org/licenses/>.

#ifndef _AUDIO_H_
#define _AUDIO_H_

#include "brux/global.hpp"

#ifdef USE_SDL2_MIXER
#include <SDL2/SDL_mixer.h>
#endif

extern const std::string& gvAudioDriver;

// Checks if audio playback is currently available

bool xyIsAudioAvailable();

// Initialize audio

void xyInitAudio();

// Unload audio

void xyUnloadAudio();

// Allocate a specific amount of channels

void xyAllocateChannels(int channels);

// Load a sound effect file from a filename

Uint32 xyLoadSound(const std::string& filename);

// Load a music file from a filename

Uint32 xyLoadMusic(const std::string& filename);

// Unload a sound effect

void xyDeleteSound(Uint32 sound);

// Unload a song

void xyDeleteMusic(Uint32 music);

// Play a sound effect

int xyPlaySound(Uint32 sound, Uint32 loops);

// Play a sound effect on a specific channel

int xyPlaySoundChannel(Uint32 sound, Uint32 loops, Uint32 channel);

// Play a song

int xyPlayMusic(Uint32 music, Uint32 loops);

// Stop a sound effect

void xyStopSound(Uint32 sound);

// Stop all audio on an audio channel

void xyStopChannel(Uint32 channel);

// Stop the currently playing music, if any

void xyStopMusic();

// Fade out the currently playing music, if any

void xyFadeMusic(int f);

// Pause the currently playing music, if any

void xyPauseMusic();

// Resume the currently playing music, if any

void xyResumeMusic();

// Check if the music is currently paused

bool xyIsMusicPaused();

// Check if any sound is playing on a specific channel

bool xyCheckSound(Uint32 channel);

// Check if any music is currently being played

bool xyCheckMusic();

// Get the number of audio channels

int xyGetAudioChannels();

// Set the music volume

void xySetMusicVolume(int volume);

#endif
