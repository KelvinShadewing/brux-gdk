//  Brux - Audio Portability API - Generic functions
//  Copyright (C) 2024 Vankata453
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
#include "brux/main.hpp"

#include "backend/audio_sdl2.hpp"
#include "backend/audio_null.hpp"

#include <simplesquirrel/vm.hpp>

BaseAudioAPI* gvAudioDriver = nullptr;

// Checks if audio playback is currently available
bool xyIsAudioAvailable() { return gvAudioDriver->isAudioAvailable(); }

// Initialize audio
void xyInitAudio() {
	xySetAudioDriver(1); // SDL2 as the default, 0 would be null backend
}

// Unload audio
void xyUnloadAudio() {
	if (gvAudioDriver != nullptr) delete gvAudioDriver;
}

// Allocate a specific amount of channels
void xyAllocateChannels(int channels) {
	gvAudioDriver->allocateChannels(channels);
}

// Load a sound effect file from a filename
Uint32 xyLoadSound(const std::string& filename) { return gvAudioDriver->loadSound(filename); }

// Load a music file from a filename
Uint32 xyLoadMusic(const std::string& filename) { return gvAudioDriver->loadMusic(filename); }

// Unload a sound effect
void xyDeleteSound(Uint32 sound) { gvAudioDriver->deleteSound(sound); }

// Unload a song
void xyDeleteMusic(Uint32 music) { gvAudioDriver->deleteMusic(music); }

// Play a sound effect
int xyPlaySound(Uint32 sound, Uint32 loops) { return gvAudioDriver->playSound(sound, loops); }

// Play a sound effect on a specific channel
int xyPlaySoundChannel(Uint32 sound, Uint32 loops, Uint32 channel) { return gvAudioDriver->playSoundChannel(sound, loops, channel); }

// Play a song
int xyPlayMusic(Uint32 music, Uint32 loops) { return gvAudioDriver->playMusic(music, loops); }

// Stop a sound effect
void xyStopSound(Uint32 sound) { gvAudioDriver->stopSound(sound); }

// Stop all audio on an audio channel
void xyStopChannel(Uint32 channel) { gvAudioDriver->stopSound(channel); }

// Stop the currently playing music, if any
void xyStopMusic() { gvAudioDriver->stopMusic(); }

// Fade out the currently playing music, if any
void xyFadeMusic(int f) { gvAudioDriver->fadeMusic(f); }

// Pause the currently playing music, if any
void xyPauseMusic() { gvAudioDriver->pauseMusic(); }

// Resume the currently playing music, if any
void xyResumeMusic() { gvAudioDriver->resumeMusic(); }

// Check if the music is currently paused
bool xyIsMusicPaused() { return gvAudioDriver->isMusicPaused(); }

// Check if any sound is playing on a specific channel
bool xyCheckSound(Uint32 channel) { return gvAudioDriver->isSoundPlaying(channel); }

// Check if any music is currently being played
bool xyCheckMusic() { return gvAudioDriver->isMusicPlaying(); }

// Get the number of audio channels
int xyGetAudioChannels() {
	if (gvAudioDriver == nullptr) return 0;
	return gvAudioDriver->getChannelCount();
}

// Get the current music volume
int xyGetMusicVolume() {
	return gvVolumeMusic;
}

// Get the current sound volume
int xyGetSoundVolume() {
	return gvVolumeSound;
}

// Set the sound volume
void xySetSoundVolume(int volume) {
	gvVolumeSound = volume;
}
void xySetMusicVolume(int volume) {
	gvVolumeMusic = volume;
	gvAudioDriver->setMusicVolume(volume);
}

// Same as below
std::string xyGetAudioDriver() {
	xyPrint("'getAudioDriver' is deprecated, use 'getAudioDriverName' instead.");
	return xyGetAudioDriverName();
}

// Get the current audio driver
std::string xyGetAudioDriverName() {
	if (gvAudioDriver == nullptr) return "Null";
	return gvAudioDriver->mAudioDriverName;
}

void xySetAudioDriver(int kind) {
	//xyPrint("setAudioDriver(%d)", kind);
	if (gvAudioDriver != nullptr) delete gvAudioDriver;

	switch (kind) {
	default:
	case 1:
		gvAudioDriver = new SDL2AudioBackend;
		break;
	case 0:
		gvAudioDriver = new NullAudioBackend;
		break;
	}

	xyPrint("Audio driver set to '%s'", gvAudioDriver->mAudioDriverName.c_str());
}

void xyRegisterAudioAPI(ssq::VM& vm) {
	vm.addFunc("loadSound", xyLoadSound); // Doc'd
	vm.addFunc("loadMusic", xyLoadMusic); // Doc'd
	vm.addFunc("playSound", xyPlaySound); // Doc'd
	vm.addFunc("playSoundChannel", xyPlaySoundChannel);
	vm.addFunc("playMusic", xyPlayMusic); // Doc'd
	vm.addFunc("deleteSound", xyDeleteSound); // Doc'd
	vm.addFunc("deleteMusic", xyDeleteMusic); // Doc'd
	vm.addFunc("stopSound", xyStopSound); // Doc'd
	vm.addFunc("stopMusic", xyStopMusic); // Doc'd
	vm.addFunc("stopChannel", xyStopChannel); // Doc'd
	vm.addFunc("checkSound", xyCheckSound); // Doc'd
	vm.addFunc("checkMusic", xyCheckMusic); // Doc'd
	vm.addFunc("setMaxChannels", xyAllocateChannels); // Doc'd
	vm.addFunc("pauseMusic", xyPauseMusic); // Doc'd
	vm.addFunc("resumeMusic", xyResumeMusic); // Doc'd
	vm.addFunc("musicPaused", xyIsMusicPaused); // Doc'd
	vm.addFunc("fadeMusic", xyFadeMusic); // Doc'd
	vm.addFunc("setMusicVolume", xySetMusicVolume); // Doc'd
	vm.addFunc("setSoundVolume", xySetSoundVolume); // Doc'd
	vm.addFunc("getMusicVolume", xyGetMusicVolume); // Doc'd
	vm.addFunc("getSoundVolume", xyGetSoundVolume); // Doc'd
	vm.addFunc("getAudioDriver", xyGetAudioDriver); // Doc'd
	vm.addFunc("getAudioDriverName", xyGetAudioDriverName);
	vm.addFunc("setAudioDriver", xySetAudioDriver);
	vm.addFunc("isAudioAvailable", xyIsAudioAvailable); // Doc'd
}
