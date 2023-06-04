//  Brux - Audio Portability API - SDL2
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

#ifdef USE_SDL2_MIXER

std::vector<Mix_Chunk*> vcSounds;
std::vector<Mix_Music*> vcMusic;

#ifdef USE_FASTFILL
std::vector<Uint32> unloadedSounds;
std::vector<Uint32> unloadedMusic;
#endif

const std::string& gvAudioDriver = "SDL2";

// Checks if audio playback is currently available

bool xyIsAudioAvailable() {
	return true; // TODO: detect if the audio stack works properly
}

// Initialize audio

void xyInitAudio() {
	#ifdef USE_FASTFILL
	xyPrint(0, "Audio system: SDL2 (fastfill enabled)");
	#else
	xyPrint(0, "Audio system: SDL2 (fastfill disablec)");
	#endif

	// Historically, brux-gdk used a 22050Hz sampling rate.
	// I can't think of any good reason for that, and it makes the audio quality worse, so I've changed it to a more reasonable 44.1kHz.

	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
		xyPrint(0, "SDL_mixer could not initialize! SDL_mixer error: %s\n", Mix_GetError());
		return;
	}

	vcSounds.push_back(0);
	vcMusic.push_back(0);
}

void xyUnloadAudio() {
	for (int i = 0; i < static_cast<int>(vcSounds.size()); i++) {
		xyDeleteSound(i);
	}

	for (int i = 0; i < static_cast<int>(vcMusic.size()); i++) {
		xyDeleteMusic(i);
	}

	Mix_Quit();
}

// Allocate a specific amount of channels

void xyAllocateChannels(int channels) {
	Mix_AllocateChannels(channels);
}

// Load a sound effect file from a filename

Uint32 xyLoadSound(const std::string& filename) {
	// Load the sound file with Mix_LoadWAV()
	
	Mix_Chunk* newSnd = Mix_LoadWAV(filename.c_str());
	if(newSnd == 0){
		xyPrint(0, "Failed to load %s! SDL_Mixer Error: %s\n", filename.c_str(), Mix_GetError());
	}

	// If the array is empty, push the sound onto it and return the first index.
	
	if (vcSounds.empty()) {
		vcSounds.push_back(newSnd);
		return 0;
	}

	// Fastfill works by using a vector of integers to store the last unloaded IDs.
	// Once we need a new sound to be loaded, we can just use the first ID in the array and pop it from the array when we're done.

	#ifdef USE_FASTFILL
	if (!unloadedSounds.empty()) {
		int id = unloadedSounds[0];

		unloadedSounds.erase(unloadedSounds.begin());

		vcSounds[id] = newSnd;
		return id;
	}
	#endif
	
	int arraySize = static_cast<int>(vcSounds.size());
	
	// If the array isn't empty, try to figure out if there are any unloaded sounds that we can replace with a new sound.
	// Note that i has to start at 1, or it will overwrite the first element that it pushes onto the array, which causes some things (most notably the star powerup in SuperTux Advance) to break.
	// This is disabled by default, and the fastfill algorithm is used instead.

	#ifndef USE_FASTFILL

	int i;
		
	for (i = 1; i < arraySize - 1; i++) {
		if (vcSounds[i] == NULL) {
			vcSounds[i] = newSnd;
			return i;
			break;
		}
	}

	#endif

	// However, if we can't find an unloaded slot to use we'll need to add it as a new array element.
	
	vcSounds.push_back(newSnd);
	
	// Yes, I know that this was originally supposed to subtract 1 from the length, and no, this is not a bug. We're using the length value before we added the element, so it ends up being correct.
	
	return arraySize;
};

// Load a music file from a filename

Uint32 xyLoadMusic(const std::string& filename) {
	// Load the music file with Mix_LoadMUS()
	
	Mix_Music* newMsc = Mix_LoadMUS(filename.c_str());
	
	// If SDL2 couldn't load it, show an error message with xyPrint()
	
	if(newMsc == 0) {
		xyPrint(0, "Failed to load %s! SDL_Mixer Error: %s\n", filename.c_str(), Mix_GetError());
	}
	
	// If the array is empty, push the sound onto it and return the first index.
	
	if (vcMusic.empty()) {
		vcMusic.push_back(newMsc);
		return 0;
	}

	// Fastfill works by using an integer to store the last unloaded ID.
	// Once we need a new sound to be loaded, we can just use that ID and set the variable to -1 when we're done.
	// This approach breaks when you need to unload multiple sounds at once, in which case you will need to use the original algorithm.
	// While I don't know of any brux-gdk-based games that do that, it will eventually be solved later by using a vector to store multiple unloaded sound IDs.
	// In the meantime, you can just disable fastfill.

	// Fastfill works by using a vector of integers to store the last unloaded IDs.
	// Once we need a new sound to be loaded, we can just use the first ID in the array and pop it from the array when we're done.

	#ifdef USE_FASTFILL
	if (!unloadedMusic.empty()) {
		int id = unloadedMusic[0];

		unloadedMusic.erase(unloadedMusic.begin());

		vcMusic[id] = newMsc;
		return id;
	}
	#endif
	
	int arraySize = static_cast<int>(vcMusic.size());
	
	// If the array isn't empty, try to figure out if there are any unloaded sounds that we can replace with a new sound.
	// Note that i has to start at 1, or it will overwrite the first element that it pushes onto the array, which causes some things (most notably the star powerup in SuperTux Advance) to break.
	// This is disabled by default, and the fastfill algorithm is used instead.

	#ifndef USE_FASTFILL

	int i;
		
	for (i = 1; i < arraySize - 1; i++) {
		if (vcMusic[i] == NULL) {
			vcMusic[i] = newMsc;
			return i;
			break;
		}
	}

	#endif

	// However, if we can't find an unloaded slot to use we'll need to add it as a new array element.
	
	vcMusic.push_back(newMsc);
	
	// Yes, I know that this was originally supposed to subtract 1 from the length, and no, this is not a bug. We're using the length value before we added the element, so it ends up being correct.
	
	return arraySize;
};

// Unload a sound effect

void xyDeleteSound(Uint32 sound) {
	// If the index is more than or equal to the length of the array (and is thus invalid), don't attempt to unload it.
	
	if (sound >= vcSounds.size()) {
		return;
	}
	
	// If the index is less than 0, don't attempt to unload it.
	// The squirrel function does not seem to actually allow negative values to be passed (likely due to how squirrel handles it), but it's still unsafe to assume that it's not negative.
	
	if (0 > sound) {
		return;
	}
	
	// If the audio data has already been unloaded, don't attempt to unload it.
	// Note that Kelvin originally wrote this code to check if it's 0 instead of NULL. It does work, but it's a bad practice. Don't do that.
	
	if (vcSounds[sound] == NULL) {
		return;
	}
	
	// If it is a valid sound, unload it with Mix_FreeChunk and set the pointer in vcSounds to NULL.
	
	Mix_FreeChunk(vcSounds[sound]);
	vcSounds[sound] = NULL;

	// If fastfill is enabled, push the ID to unloadedSounds

	#ifdef USE_FASTFILL
	unloadedSounds.push_back(sound);
	#endif
};

// Unload a song

void xyDeleteMusic(Uint32 music) {
	// If the index is more than or equal to the length of the array (and is thus invalid), don't attempt to unload it.
	
	if (music >= vcMusic.size()) {
		return;
	}
	
	// If the index is less than 0, don't attempt to unload it.
	// The squirrel function does not seem to actually allow negative values to be passed (likely due to how squirrel handles it), but it's still unsafe to assume that it's not negative.
	
	if (0 > music) {
		return;
	}
	
	// If the audio data has already been unloaded, don't attempt to unload it.
	// Note that Kelvin originally wrote this code to check if it's 0 instead of NULL. It does work, but it's a bad practice. Don't do that.
	
	if (vcMusic[music] == NULL) {
		return;
	}
	
	// If it is a valid song, unload it with Mix_FreeChunk and set the pointer in vcMusic to NULL.
	
	Mix_FreeMusic(vcMusic[music]);
	vcMusic[music] = NULL;

	// If fastfill is enabled, push the ID to unloadedMusic

	#ifdef USE_FASTFILL
	unloadedMusic.push_back(music);
	#endif
};

// Play a sound effect

int xyPlaySound(Uint32 sound, Uint32 loops) {
	// Play the audio with Mix_PlayChannel()
	
	int i = Mix_PlayChannel(-1, vcSounds[sound], loops);
	
	// If it failed, log the error with xyPrint()
	
	if (i == -1) {
		xyPrint(0, "Error playing sound! SDL_Mixer Error: %s\n", Mix_GetError());
		return -1;
	}

	Mix_Volume(i, gvVolumeSound);
	
	return i;
};

// Play a sound effect on a specific channel

int xyPlaySoundChannel(Uint32 sound, Uint32 loops, Uint32 channel) {
	const int i = Mix_PlayChannel(channel, vcSounds[sound], loops);

	if (i == -1) {
		xyPrint(0, "Error playing sound! SDL_Mixer Error: %s\n", Mix_GetError());
		return -1;
	}
	
	Mix_Volume(i, gvVolumeSound);

	return i;
}

// Play a song

int xyPlayMusic(Uint32 music, Uint32 loops) {
	// Play the audio with Mix_PlayChannel()
	
	int i = Mix_PlayMusic(vcMusic[music], loops);
	
	// If it failed, log the error with xyPrint()
	
	if (i == -1) {
		xyPrint(0, "Error playing music! SDL_Mixer Error: %s\n", Mix_GetError());
		return -1;
	}

	Mix_VolumeMusic(gvVolumeMusic);
	
	return i;
};

// Stop a sound effect, no idea why it doesn't support stopping music

void xyStopSound(Uint32 sound) {
	// If the index is more than or equal to the length of the array (and is thus invalid), don't attempt to stop it.
	
	if (sound >= vcSounds.size()) {
		return;
	}
	
	// If the index is less than 0, don't attempt to stop it.
	
	if (0 > sound) {
		return;
	}
	
	// If the audio data has already been unloaded, don't attempt to unload it.
	
	if (vcSounds[sound] == NULL) {
		return;
	}
	
	// Otherwise, stop the audio on all channels using Mix_HaltChannel()

	int i;
	
	for (i = 0; i < gvMixChannels; i++) {
		if (Mix_GetChunk(i) == vcSounds[sound]) {
			Mix_HaltChannel(i);
		}
	}
};

// Stop all audio on an audio channel

void xyStopChannel(Uint32 channel) {
	Mix_HaltChannel(channel);
}

// Stop the currently playing music, if any

void xyStopMusic() {
	Mix_HaltMusic();
}

// Fade out the currently playing music, if any

void xyFadeMusic(int f) {
	Mix_FadeOutMusic(f * 1000);
}

// Pause the currently playing music, if any

void xyPauseMusic() {
	Mix_PauseMusic();
}

// Resume the currently playing music, if any

void xyResumeMusic() {
	Mix_ResumeMusic();
}

// Check if the music is currently paused

bool xyIsMusicPaused() {
	return Mix_PlayingMusic() && Mix_PausedMusic();
}

// Check if any sound is playing on a specific channel

bool xyCheckSound(Uint32 channel) {
	return Mix_Playing(channel);
}

// Check if any music is currently being played

bool xyCheckMusic() {
	return Mix_PlayingMusic();
}

// Get the number of audio channels

int xyGetAudioChannels() {
	return Mix_AllocateChannels(-8);
}

// Set the music volume

void xySetMusicVolume(int volume) {
	Mix_VolumeMusic(volume);
}

#endif