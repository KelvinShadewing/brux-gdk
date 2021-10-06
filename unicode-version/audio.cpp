/*============*\
| AUDIO SOURCE |
\*============*/

#include "main.h"
#include "global.h"
#include "audio.h"

Uint32 xyLoadSound(const char* filename) {
	//Load the sound file
	Mix_Chunk* newSnd = Mix_LoadWAV(filename);
	if(newSnd == 0){
		xyPrint(0, L"Failed to load %s! SDL_Mixer Error: %s\n", filename, Mix_GetError());
	}

	//Add the file to the list
	if(vcSounds.size() == 0){
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

Uint32 xyLoadMusic(const char* filename) {
	//Load the music file
	Mix_Music* newMsc = Mix_LoadMUS(filename);
	if(newMsc == 0) {
		xyPrint(0, L"Failed to load %s! SDL_Mixer Error: %s\n", filename, Mix_GetError());
	}

	//Add the file to the list
	if(vcMusic.size() == 0) {
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
	if(i == -1) xyPrint(0, L"Error playing sound! SDL_Mixer Error: %s\n", Mix_GetError());
	return i;
};

int xyPlayMusic(Uint32 music, Uint32 loops) {
	int i = Mix_PlayMusic(vcMusic[music], loops);
	if(i == -1) xyPrint(0, L"Error playing music! SDL_Mixer Error: %s\n", Mix_GetError());
	return i;
};
