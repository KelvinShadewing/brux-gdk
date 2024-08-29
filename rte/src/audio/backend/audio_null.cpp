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

#include "audio_null.hpp"
#include "audio/audio.hpp"
#include "brux/main.hpp"

// Initialize audio
NullAudioBackend::NullAudioBackend() : BaseAudioAPI("Null", xyBruxVersion()) {}

NullAudioBackend::~NullAudioBackend() {}

bool NullAudioBackend::isAudioAvailable() { return false; }

void NullAudioBackend::allocateChannels(int channels) { mChannels = channels; }

uint32_t NullAudioBackend::loadSound(const std::string& filename) {
	if (mLoadedSoundFiles.empty()) {
		mLoadedSoundFiles.push_back(filename);
		return 0;
	}

	// Fastfill works by using a vector of integers to store the last mUnloaded IDs.
	// Once we need a new sound to be loaded, we can just use the first ID in the array and pop it from the array when we're done.

	#ifdef USE_FASTFILL
	if (!mUnloadedSounds.empty()) {
		int id = mUnloadedSounds[0];

		mUnloadedSounds.erase(mUnloadedSounds.begin());

		mLoadedSoundFiles[id] = filename;
		return id;
	}
	#endif

	int arraySize = static_cast<int>(mLoadedSoundFiles.size());

	// If the array isn't empty, try to figure out if there are any mUnloaded sounds that we can replace with a new sound.
	// Note that i has to start at 1, or it will overwrite the first element that it pushes onto the array, which causes some things (most notably the star powerup in SuperTux Advance) to break.
	// This is disabled by default, and the fastfill algorithm is used instead.

	#ifndef USE_FASTFILL

	int i;

	for (i = 1; i < arraySize - 1; i++) {
		if (mLoadedSoundFiles[i] == NULL) {
			mLoadedSoundFiles[i] = filename;
			return i;
			break;
		}
	}

	#endif

	mLoadedSoundFiles.push_back(filename);

	return arraySize;
}

uint32_t NullAudioBackend::loadMusic(const std::string& filename) {
	if (mLoadedMusicFiles.empty()) {
		mLoadedMusicFiles.push_back(filename);
		return 0;
	}

	// Fastfill works by using a vector of integers to store the last mUnloaded IDs.
	// Once we need a new sound to be loaded, we can just use the first ID in the array and pop it from the array when we're done.

	#ifdef USE_FASTFILL
	if (!mUnloadedMusic.empty()) {
		int id = mUnloadedMusic[0];

		mUnloadedMusic.erase(mUnloadedMusic.begin());

		mLoadedMusicFiles[id] = filename;
		return id;
	}
	#endif

	int arraySize = static_cast<int>(mLoadedMusicFiles.size());

	// If the array isn't empty, try to figure out if there are any mUnloaded sounds that we can replace with a new sound.
	// Note that i has to start at 1, or it will overwrite the first element that it pushes onto the array, which causes some things (most notably the star powerup in SuperTux Advance) to break.
	// This is disabled by default, and the fastfill algorithm is used instead.

	#ifndef USE_FASTFILL

	int i;

	for (i = 1; i < arraySize - 1; i++) {
		if (mLoadedMusicFiles[i] == NULL) {
			mLoadedMusicFiles[i] = filename;
			return i;
			break;
		}
	}

	#endif

	mLoadedMusicFiles.push_back(filename);

	return arraySize;
}

void NullAudioBackend::deleteSound(uint32_t sound) {
	if (sound >= mLoadedSoundFiles.size()) return;

	mLoadedSoundFiles[sound] = "";

	#ifdef USE_FASTFILL
	mUnloadedSounds.push_back(sound);
	#endif
}

void NullAudioBackend::deleteMusic(uint32_t music) {
	if (music >= mLoadedMusicFiles.size()) return;

	mLoadedMusicFiles[music] = "";

	#ifdef USE_FASTFILL
	mUnloadedMusic.push_back(music);
	#endif
}

int NullAudioBackend::playSound(uint32_t sound, uint32_t loops) { return 0; }

int NullAudioBackend::playSoundChannel(uint32_t sound, uint32_t loops, uint32_t channel) { return 0; }

int NullAudioBackend::playMusic(uint32_t music, uint32_t loops) { return 0; }

void NullAudioBackend::stopSound(uint32_t sound) {}

void NullAudioBackend::stopChannel(uint32_t channel) {}

void NullAudioBackend::stopMusic() {}

void NullAudioBackend::fadeMusic(int f) {}

void NullAudioBackend::pauseMusic() {}

void NullAudioBackend::resumeMusic() {}

bool NullAudioBackend::isMusicPaused() {
	return false;
}

bool NullAudioBackend::isSoundPlaying(int channel) {
	return false;
}

bool NullAudioBackend::isMusicPlaying() {
	return false;
}

int NullAudioBackend::getChannelCount() {
	return mChannels;
}

void NullAudioBackend::setMusicVolume(uint32_t volume) {
	gvVolumeMusic = volume;
}
