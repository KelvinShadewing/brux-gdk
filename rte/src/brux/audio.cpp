//  Brux - Audio
//  Copyright (C) 2016 KelvinShadewing
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

/*============*\
| AUDIO SOURCE |
\*============*/

#include "brux/main.hpp"
#include "brux/global.hpp"
#include "brux/audio.hpp"

Uint32 xyLoadSound(const std::string& filename) {
	//Load the sound file
	Mix_Chunk* newSnd = Mix_LoadWAV(filename.c_str());
	if(newSnd == 0){
		xyPrint(0, "Failed to load %s! SDL_Mixer Error: %s\n", filename.c_str(), Mix_GetError());
	}

	//Add the file to the list
	if(vcSounds.empty()){
		vcSounds.push_back(newSnd);
		return 0;
	} else {
		//Check for an open space in the list
		for(int i = 1; i < vcSounds.size(); i++){
			if(vcSounds[i] == 0){
				vcSounds[i] = newSnd;
				return i;
				break;
			}
		}
	}

	//If an open space wasn't found
	vcSounds.push_back(newSnd);
	return vcSounds.size() - 1;
};

Uint32 xyLoadMusic(const std::string& filename) {
	//Load the music file
	Mix_Music* newMsc = Mix_LoadMUS(filename.c_str());
	if(newMsc == 0) {
		xyPrint(0, "Failed to load %s! SDL_Mixer Error: %s\n", filename.c_str(), Mix_GetError());
	}

	//Add the file to the list
	if(vcMusic.empty()) {
		vcMusic.push_back(newMsc);
		return 0;
	} else {
		//Check for an open space in the list
		for(int i = 1; i < vcMusic.size(); i++) {
			if(vcMusic[i] == 0) {
				vcMusic[i] = newMsc;
				return i;
				break;
			}
		}
	}

	//If an open space wasn't found
	vcMusic.push_back(newMsc);
	return vcMusic.size() - 1;
};

void xyDeleteSound(Uint32 sound) {
	if(sound >= vcSounds.size()) return;
	if(vcSounds[sound] == 0) return;
	Mix_FreeChunk(vcSounds[sound]);
	vcSounds[sound] = 0;
};

void xyDeleteMusic(Uint32 music) {
	if(music >= vcMusic.size()) return;
	if(vcMusic[music] == 0) return;
	Mix_FreeMusic(vcMusic[music]);
	vcMusic[music] = 0;
};

int xyPlaySound(Uint32 sound, Uint32 loops) {
	int i = Mix_PlayChannel(-1, vcSounds[sound], loops);
	if(i == -1) xyPrint(0, "Error playing sound! SDL_Mixer Error: %s\n", Mix_GetError());
	return i;
};

int xyPlayMusic(Uint32 music, Uint32 loops) {
	int i = Mix_PlayMusic(vcMusic[music], loops);
	if(i == -1) xyPrint(0, "Error playing music! SDL_Mixer Error: %s\n", Mix_GetError());
	return i;
};

void xyStopSound(Uint32 sound) {
	if(sound < 0 || sound >= vcSounds.size()) return;
	if(vcSounds[sound] == 0) return;

	for(int i = 0; i < gvMixChannels; i++) {
		if(Mix_GetChunk(i) == vcSounds[sound]) Mix_HaltChannel(i);
	}
};
