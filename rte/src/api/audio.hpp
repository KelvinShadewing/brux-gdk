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

#ifndef BRUX_API_AUDIO_HEADER
#define BRUX_API_AUDIO_HEADER

#ifndef BRUX_API_GEN

#include <string>

#endif

namespace BruxAPI {

// Audio
int loadSound(const std::string& s); // Doc'd
int loadMusic(const std::string& m); // Doc'd
int playSound(int s, int l); // Doc'd
int playSoundChannel(int s, int l, int c);
void playMusic(int m, int l); // Doc'd
void deleteSound(int s); // Doc'd
void deleteMusic(int m); // Doc'd
void stopSound(int s); // Doc'd
void stopMusic(); // Doc'd
void stopChannel(int c); // Doc'd
bool checkSound(int c); // Doc'd
bool checkMusic(); // Doc'd
void setMaxChannels(int c); // Doc'd
void pauseMusic(); // Doc'd
void resumeMusic(); // Doc'd
bool musicPaused(); // Doc'd
void fadeMusic(int f); // Doc'd
void setMusicVolume(int vol); // Doc'd
void setSoundVolume(int vol); // Doc'd
int getMusicVolume(); // Doc'd
int getSoundVolume(); // Doc'd
const std::string& getAudioDriver(); // Doc'd
bool isAudioAvailable(); // Doc'd

} // namespace BruxAPI

#endif
