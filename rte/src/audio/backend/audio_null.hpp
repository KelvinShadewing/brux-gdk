#pragma once

#include <audio/audio.hpp>

class NullAudioBackend final : public BaseAudioAPI {
public:
	NullAudioBackend();
	~NullAudioBackend();

	// Functions
	int getChannelCount() override;
	void allocateChannels(int channelCount) override;

	void deleteSound(uint32_t sound) override;
	void deleteMusic(uint32_t music) override;

	uint32_t loadSound(const std::string& path) override;
	uint32_t loadMusic(const std::string& path) override;

	int playSound(uint32_t sound, uint32_t loops) override;
	int playSoundChannel(uint32_t sound, uint32_t loops, uint32_t channel) override;
	int playMusic(uint32_t sound, uint32_t loops) override;

	void setMusicVolume(uint32_t volume) override;

	void stopSound(uint32_t sound) override;
	void stopChannel(uint32_t channel) override;
	void stopMusic() override;

	void pauseMusic() override;
	void resumeMusic() override;
	void fadeMusic(int f) override;

	bool isSoundPlaying(int channel) override;
	bool isMusicPlaying() override;

	bool isMusicPaused() override;

	bool isAudioAvailable() override;

	// Member Variables
	int mChannels;
};
