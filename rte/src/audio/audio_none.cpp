//  Brux - Audio Portability API - Generic Fallback
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

#include "audio/audio.hpp"

#ifndef USE_SDL2_MIXER

const std::string& gvAudioDriver = "None";

// Checks if audio playback is currently available

bool xyIsAudioAvailable() {
	return false; // This driver doesn't actually handle audio, so playback is never available.
}

// Initialize audio

void xyInitAudio() {
	xyPrint(0, "Audio system: None");
}

// Unload audio

void xyUnloadAudio() {
	// We don't need to do anything here, as this doesn't actually handle audio.
}

// Allocate a specific amount of channels

void xyAllocateChannels(int channels) {
	// We don't need to do anything here, as this doesn't actually have any audio channels.
}

Uint32 xyLoadSound(const std::string& filename) {
	return 0;
};

// Load a music file from a filename

Uint32 xyLoadMusic(const std::string& filename) {
	return 0;
};

// Unload a sound effect

void xyDeleteSound(Uint32 sound) {
	// We don't need to do anything here, as the audio it's trying to unload doesn't exist anyways.
};

// Unload a song

void xyDeleteMusic(Uint32 music) {
	// We don't need to do anything here, as the audio it's trying to unload doesn't exist anyways.
};

// Play a sound effect

int xyPlaySound(Uint32 sound, Uint32 loops) {
	return 0;
};

// Play a sound effect on a specific channel

int xyPlaySoundChannel(Uint32 sound, Uint32 loops, Uint32 channel) {
	return 0;
}

// Play a song

int xyPlayMusic(Uint32 music, Uint32 loops) {
	return 0;
};

// Stop a sound effect, no idea why it doesn't support stopping music

void xyStopSound(Uint32 sound) {
	// We don't need to do anything here, as the audio it's trying to stop doesn't exist anyways.
};

// Stop all audio on an audio channel

void xyStopChannel(Uint32 channel) {
	// We don't need to do anything here, as the audio it's trying to stop doesn't exist anyways.
}

// Stop the currently playing music, if any

void xyStopMusic() {
	// We don't need to do anything here, as the audio it's trying to stop doesn't exist anyways.
}

// Fade out the currently playing music, if any

void xyFadeMusic(int f) {
	// We don't need to do anything here, as the audio it's trying to fade out doesn't exist anyways.
}

// Pause the currently playing music, if any

void xyPauseMusic() {
	// We don't need to do anything here, as the audio it's trying to pause doesn't exist anyways.
}

// Resume the currently playing music, if any

void xyResumeMusic() {
	// We don't need to do anything here, as the audio it's trying to resume doesn't exist anyways.
}

// Check if the music is currently paused

bool xyIsMusicPaused() {
	return false;
}

// Check if any sound is playing on a specific channel

bool xyCheckSound(Uint32 channel) {
	// No audio will ever be played by this fallback driver, so we just return false.

	return false;
}

// Check if any music is currently being played

bool xyCheckMusic() {
	// No audio will ever be played by this fallback driver, so we just return false.

	return false;
}

// Get the number of audio channels

int xyGetAudioChannels() {
	return 0;
}

// Set the music volume

void xySetMusicVolume(int volume) {
	// We don't need to do anything here, as this doesn't actually play any audio
}

#endif