#include "api/audio.hpp"

#include "brux/main.hpp"

#include "brux/audio.hpp"
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
	const int c = xyPlaySound(s, l);
	if (c != -1)
		Mix_Volume(c, gvVolumeSound);

	return c;
}

int playSoundChannel(int s, int l, int c) {
	const int i = Mix_PlayChannel(c, vcSounds[s], l);
	if (i == -1) {
		std::stringstream err;
		err << "Error playing sound! SDL_Mixer Error: " << Mix_GetError() << std::endl;
		throw std::runtime_error(err.str());
	}
	else {
		Mix_Volume(i, gvVolumeSound);
	}

	return i;
}

void playMusic(int m, int l) {
	xyPlayMusic(m, l);
	Mix_VolumeMusic(gvVolumeMusic);
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
	Mix_HaltMusic();
}

void stopChannel(int c) {
	Mix_HaltChannel(c);
}

bool checkSound(int c) {
	return Mix_Playing(c);
}

bool checkMusic() {
	return Mix_PlayingMusic();
}

void setMaxChannels(int c) {
	Mix_AllocateChannels(c);
}

void pauseMusic() {
	Mix_PauseMusic();
}

void resumeMusic() {
	Mix_ResumeMusic();
}

bool musicPaused() {
	return Mix_PlayingMusic() && Mix_PausedMusic();
}

void fadeMusic(float f) {
	Mix_FadeOutMusic(f * 1000.0);
}

void setMusicVolume(int vol) {
	gvVolumeMusic = vol;
	Mix_VolumeMusic(vol);
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

} // namespace BruxAPI
