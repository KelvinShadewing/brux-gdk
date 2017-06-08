/*============*\
| AUDIO SOURCE |
\*============*/

#include "main.h"
#include "global.h"
#include "audio.h"

Uint32 xyNewSound(const char* filename){
	//Load the sound file
	Mix_Chunk* newSnd = Mix_LoadWAV(filename);
	if(newSnd == 0){
		xyPrint(0, "Failed to load %s! SDL_mixer Error: %s\n", filename, Mix_GetError());
	};

	//Add the file to the list
	if(vcSounds.size() == 0){
		vcSounds.push_back(newSnd);
		return 0;
	} else {
		//Check for an open space on the list
		for(int i = 1; i < vcSounds.size(); i++){
			if(vcSounds[i] == 0){
				vcSounds[i] = newSnd;
				return i;
				break;
			};
		};
	};

	//If an open space wasn't found
	vcSounds.push_back(newSnd);
	return vcSounds.size() - 1;
};

void xyDeleteSound(Uint32 sound){
};

void xyDeleteMusic(Uint32 music){
};