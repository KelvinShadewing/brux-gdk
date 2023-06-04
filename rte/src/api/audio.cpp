//  Brux - Audio API
//  Copyright (C) 2016 KelvinShadewing
//  Copyright (C) 2023 Vankata453
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

#include "api/audio.hpp"

#include "brux/main.hpp"

#include "audio/audio.hpp"
#include "brux/global.hpp"

namespace BruxAPI {

///////////
// AUDIO //
///////////

int loadSound(const std::string& s) {
	return xyLoadSound(s);
}

int loadMusic(const std::string& m) {
	return xyLoadMusic(m);
}

int playSound(int s, int l) {
	return xyPlaySound(s, l);
}

int playSoundChannel(int s, int l, int c) {
	return xyPlaySoundChannel(s, l, c);
}

void playMusic(int m, int l) {
	xyPlayMusic(m, l);
}

void deleteSound(int s) {
	xyDeleteSound(s);
}

void deleteMusic(int m) {
	xyDeleteMusic(m);
}

void stopSound(int s) {
	xyStopSound(s);
}

void stopMusic() {
	xyStopMusic();
}

void stopChannel(int c) {
	xyStopChannel(c);
}

bool checkSound(int c) {
	return xyCheckSound(c);
}

bool checkMusic() {
	return xyCheckMusic();
}

void setMaxChannels(int c) {
	xyAllocateChannels(c);
}

void pauseMusic() {
	xyPauseMusic();
}

void resumeMusic() {
	xyResumeMusic();
}

bool musicPaused() {
	return xyIsMusicPaused();
}

void fadeMusic(int f) {
	xyFadeMusic(f);
}

void setMusicVolume(int vol) {
	gvVolumeMusic = vol;
	xySetMusicVolume(vol);
}

void setSoundVolume(int vol) {
	gvVolumeSound = vol;
}

int getMusicVolume() {
	return gvVolumeMusic;
}

int getSoundVolume() {
	return gvVolumeSound;
}

const std::string& getAudioDriver() {
	return gvAudioDriver;
}

bool isAudioAvailable() {
	return xyIsAudioAvailable();
}

} // namespace BruxAPI
