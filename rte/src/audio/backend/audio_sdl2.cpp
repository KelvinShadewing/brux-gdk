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

#include "audio_sdl2.hpp"
#include "audio/audio.hpp"
#include <SDL_mixer.h>
#include <SDL_version.h>

bool isAudioLoaded = false;
bool didAudioLoadFail = false;

// Checks if audio playback is currently available
// NOTE: It doesn't appear to be possible to get the system volume using SDL2.



// JANK
std::string SDL2VersionToString(const SDL_version* ver) {
	return (char)ver->major + (std::string)"." + (char)ver->minor + (std::string) + "." + (char)ver->patch;
}

// Initialize audio
SDL2AudioBackend::SDL2AudioBackend() : BaseAudioAPI("SDL2", SDL2VersionToString(Mix_Linked_Version())) {
	#ifdef USE_FASTFILL
	xyPrint("Audio system: SDL2 (fastfill enabled)");
	#else
	xyPrint("Audio system: SDL2 (fastfill disabled)");
	#endif

	// Historically, brux-gdk used a 22050Hz sampling rate.
	// I can't think of any good reason for that, and it makes the audio quality worse, so I've changed it to a more reasonable 44.1kHz.

	SDL_InitSubSystem(SDL_INIT_AUDIO);

	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) != 0) {
		xyPrint("SDL_mixer could not initialize! SDL_mixer error: %s\n", Mix_GetError());
		didAudioLoadFail = true;
		isAudioLoaded = false;
		return;
	}

	didAudioLoadFail = false;

	isAudioLoaded = true;

	mVcSounds.push_back(0);
	mVcMusic.push_back(0);
}

SDL2AudioBackend::~SDL2AudioBackend() {
	for (int i = 0; i < static_cast<int>(mVcSounds.size()); i++) {
		deleteSound(i);
	}

	for (int i = 0; i < static_cast<int>(mVcMusic.size()); i++) {
		deleteMusic(i);
	}

	Mix_Quit();

	SDL_QuitSubSystem(SDL_INIT_AUDIO);
}

bool SDL2AudioBackend::isAudioAvailable() {
	xyPrint("Audio Available: %d, %d", isAudioLoaded, !didAudioLoadFail);
	return isAudioLoaded && !didAudioLoadFail;
}

// Allocate a specific amount of channels

void SDL2AudioBackend::allocateChannels(int channels) {
	Mix_AllocateChannels(channels);
}

// Load a sound effect file from a filename

uint32_t SDL2AudioBackend::loadSound(const std::string& filename) {
	// Load the sound file with Mix_LoadWAV()

	Mix_Chunk* newSnd = Mix_LoadWAV(filename.c_str());

	if (newSnd == 0){
		xyPrint("Failed to load %s! SDL_Mixer Error: %s\n", filename.c_str(), Mix_GetError());
	}

	// If the array is empty, push the sound onto it and return the first index.

	if (mVcSounds.empty()) {
		mVcSounds.push_back(newSnd);
		mLoadedSoundFiles.push_back(filename);
		return 0;
	}

	// Fastfill works by using a vector of integers to store the last mUnloaded IDs.
	// Once we need a new sound to be loaded, we can just use the first ID in the array and pop it from the array when we're done.

	#ifdef USE_FASTFILL
	if (!mUnloadedSounds.empty()) {
		int id = mUnloadedSounds[0];

		mUnloadedSounds.erase(mUnloadedSounds.begin());

		mVcSounds[id] = newSnd;
		mLoadedSoundFiles[id] = filename;

		return id;
	}
	#endif

	int arraySize = static_cast<int>(mVcSounds.size());

	// If the array isn't empty, try to figure out if there are any mUnloaded sounds that we can replace with a new sound.
	// Note that i has to start at 1, or it will overwrite the first element that it pushes onto the array, which causes some things (most notably the star powerup in SuperTux Advance) to break.
	// This is disabled by default, and the fastfill algorithm is used instead.

	#ifndef USE_FASTFILL

	int i;

	for (i = 1; i < arraySize - 1; i++) {
		if (mVcSounds[i] == NULL) {
			mVcSounds[i] = newSnd;
			return i;
			break;
		}
	}

	#endif

	// However, if we can't find an mUnloaded slot to use we'll need to add it as a new array element.

	mVcSounds.push_back(newSnd);
	mLoadedSoundFiles.push_back(filename);

	// Yes, I know that this was originally supposed to subtract 1 from the length, and no, this is not a bug. We're using the length value before we added the element, so it ends up being correct.

	return arraySize;
}

// Load a music file from a filename

uint32_t SDL2AudioBackend::loadMusic(const std::string& filename) {
	// Load the music file with Mix_LoadMUS()

	Mix_Music* newMsc = Mix_LoadMUS(filename.c_str());

	// If SDL2 couldn't load it, show an error message with xyPrint()

	if(newMsc == 0) {
		xyPrint("Failed to load %s! SDL_Mixer Error: %s\n", filename.c_str(), Mix_GetError());
	}

	// If the array is empty, push the sound onto it and return the first index.

	if (mVcMusic.empty()) {
		mVcMusic.push_back(newMsc);
		mLoadedMusicFiles.push_back(filename);
		return 0;
	}

	// Fastfill works by using an integer to store the last mUnloaded ID.
	// Once we need a new sound to be loaded, we can just use that ID and set the variable to -1 when we're done.
	// This approach breaks when you need to unload multiple sounds at once, in which case you will need to use the original algorithm.
	// While I don't know of any brux-gdk-based games that do that, it will eventually be solved later by using a vector to store multiple mUnloaded sound IDs.
	// In the meantime, you can just disable fastfill.

	// Fastfill works by using a vector of integers to store the last mUnloaded IDs.
	// Once we need a new sound to be loaded, we can just use the first ID in the array and pop it from the array when we're done.

	#ifdef USE_FASTFILL
	if (!mUnloadedMusic.empty()) {
		int id = mUnloadedMusic[0];

		if (id < mLoadedMusicFiles.size()) {
			mUnloadedMusic.erase(mUnloadedMusic.begin());


			mVcMusic[id] = newMsc;
			mLoadedMusicFiles[id] = filename;
			return id;
		}
	}
	#endif

	int arraySize = static_cast<int>(mVcMusic.size());

	// If the array isn't empty, try to figure out if there are any mUnloaded sounds that we can replace with a new sound.
	// Note that i has to start at 1, or it will overwrite the first element that it pushes onto the array, which causes some things (most notably the star powerup in SuperTux Advance) to break.
	// This is disabled by default, and the fastfill algorithm is used instead.

	#ifndef USE_FASTFILL

	int i;

	for (i = 1; i < arraySize - 1; i++) {
		if (mVcMusic[i] == NULL) {
			mVcMusic[i] = newMsc;
			mLoadedMusicFiles[i] = filename;
			return i;
			break;
		}
	}

	#endif

	// However, if we can't find an mUnloaded slot to use we'll need to add it as a new array element.

	mVcMusic.push_back(newMsc);
	mLoadedMusicFiles.push_back(filename);

	// Yes, I know that this was originally supposed to subtract 1 from the length, and no, this is not a bug. We're using the length value before we added the element, so it ends up being correct.

	return arraySize;
}

// Unload a sound effect

void SDL2AudioBackend::deleteSound(uint32_t sound) {
	// If the index is more than or equal to the length of the array (and is thus invalid), don't attempt to unload it.

	if (sound >= mVcSounds.size()) {
		return;
	}

	// If the index is less than 0, don't attempt to unload it.
	// The squirrel function does not seem to actually allow negative values to be passed (likely due to how squirrel handles it), but it's still unsafe to assume that it's not negative.

	if (0 > sound) {
		return;
	}

	// If the audio data has already been mUnloaded, don't attempt to unload it.
	// Note that Kelvin originally wrote this code to check if it's 0 instead of NULL. It does work, but it's a bad practice. Don't do that.

	if (mVcSounds[sound] == NULL) {
		return;
	}

	// If it is a valid sound, unload it with Mix_FreeChunk and set the pointer in mVcSounds to NULL.

	Mix_FreeChunk(mVcSounds[sound]);
	mVcSounds[sound] = NULL;

	// If fastfill is enabled, push the ID to mUnloadedSounds

	#ifdef USE_FASTFILL
	mUnloadedSounds.push_back(sound);
	#endif
}

// Unload a song

void SDL2AudioBackend::deleteMusic(uint32_t music) {
	// If the index is more than or equal to the length of the array (and is thus invalid), don't attempt to unload it.

	if (music >= mVcMusic.size()) {
		return;
	}

	// If the index is less than 0, don't attempt to unload it.
	// The squirrel function does not seem to actually allow negative values to be passed (likely due to how squirrel handles it), but it's still unsafe to assume that it's not negative.

	if (music == 0) {
		return;
	}

	// If the audio data has already been mUnloaded, don't attempt to unload it.
	// Note that Kelvin originally wrote this code to check if it's 0 instead of NULL. It does work, but it's a bad practice. Don't do that.

	if (mVcMusic[music] == NULL) {
		return;
	}

	// If it is a valid song, unload it with Mix_FreeChunk and set the pointer in mVcMusic to NULL.

	Mix_FreeMusic(mVcMusic[music]);
	mVcMusic[music] = NULL;

	// If fastfill is enabled, push the ID to mUnloadedMusic

	#ifdef USE_FASTFILL
	mUnloadedMusic.push_back(music);
	#endif
}

// Play a sound effect

int SDL2AudioBackend::playSound(uint32_t sound, uint32_t loops) {
	// Play the audio with Mix_PlayChannel()

	int i = Mix_PlayChannel(-1, mVcSounds[sound], loops);

	// If it failed, log the error with xyPrint()

	if (i == -1) {
		xyPrint("Error playing sound! SDL_Mixer Error: %s\n", Mix_GetError());
		return -1;
	}

	Mix_Volume(i, gvVolumeSound);

	return i;
}

// Play a sound effect on a specific channel

int SDL2AudioBackend::playSoundChannel(uint32_t sound, uint32_t loops, uint32_t channel) {
	const int i = Mix_PlayChannel(channel, mVcSounds[sound], loops);

	if (i == -1) {
		xyPrint("Error playing sound! SDL_Mixer Error: %s\n", Mix_GetError());
		return -1;
	}

	Mix_Volume(i, gvVolumeSound);

	return i;
}

// Play a song

int SDL2AudioBackend::playMusic(uint32_t music, uint32_t loops) {
	// Play the audio with Mix_PlayChannel()

	int i = Mix_PlayMusic(mVcMusic[music], loops);

	// If it failed, log the error with xyPrint()

	if (i == -1) {
		xyPrint("Error playing music! SDL_Mixer Error: %s\n", Mix_GetError());
		return -1;
	}

	Mix_VolumeMusic(gvVolumeMusic);

	return i;
}

// Stop a sound effect, no idea why it doesn't support stopping music

void SDL2AudioBackend::stopSound(uint32_t sound) {
	// If the index is more than or equal to the length of the array (and is thus invalid), don't attempt to stop it.

	if (sound >= mVcSounds.size()) {
		return;
	}

	// If the index is less than 0, don't attempt to stop it.

	if (0 > sound) {
		return;
	}

	// If the audio data has already been mUnloaded, don't attempt to unload it.

	if (mVcSounds[sound] == NULL) {
		return;
	}

	// Otherwise, stop the audio on all channels using Mix_HaltChannel()

	int i;

	for (i = 0; i < gvMixChannels; i++) {
		if (Mix_GetChunk(i) == mVcSounds[sound]) {
			Mix_HaltChannel(i);
		}
	}
}

// Stop all audio on an audio channel

void SDL2AudioBackend::stopChannel(uint32_t channel) {
	Mix_HaltChannel(channel);
}

// Stop the currently playing music, if any

void SDL2AudioBackend::stopMusic() {
	Mix_HaltMusic();
}

// Fade out the currently playing music, if any

void SDL2AudioBackend::fadeMusic(int f) {
	Mix_FadeOutMusic(f * 1000);
}

// Pause the currently playing music, if any

void SDL2AudioBackend::pauseMusic() {
	Mix_PauseMusic();
}

// Resume the currently playing music, if any

void SDL2AudioBackend::resumeMusic() {
	Mix_ResumeMusic();
}

// Check if the music is currently paused

bool SDL2AudioBackend::isMusicPaused() {
	return Mix_PlayingMusic() && Mix_PausedMusic();
}

// Check if any sound is playing on a specific channel

bool SDL2AudioBackend::isSoundPlaying(int channel) {
	return Mix_Playing(channel);
}

// Check if any music is currently being played

bool SDL2AudioBackend::isMusicPlaying() {
	return Mix_PlayingMusic();
}

// Get the number of audio channels

int SDL2AudioBackend::getChannelCount() {
	return Mix_AllocateChannels(-8);
}

// Set the music volume

void SDL2AudioBackend::setMusicVolume(uint32_t volume) {
	gvVolumeMusic = volume;
	Mix_VolumeMusic(volume);
}
