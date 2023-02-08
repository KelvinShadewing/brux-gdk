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
void fadeMusic(float f); // Doc'd
void setMusicVolume(int vol); // Doc'd
void setSoundVolume(int vol); // Doc'd
int getMusicVolume(); // Doc'd
int getSoundVolume(); // Doc'd

} // namespace BruxAPI

#endif
