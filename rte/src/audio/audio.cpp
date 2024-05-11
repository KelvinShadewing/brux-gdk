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

#include <simplesquirrel/vm.hpp>

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

// Get the current audio driver

std::string xyGetAudioDriver() {
	return gvAudioDriver;
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
	vm.addFunc("isAudioAvailable", xyIsAudioAvailable); // Doc'd
}
