#ifndef BRUX_API_MAIN_HEADER
#define BRUX_API_MAIN_HEADER

#ifndef BRUX_API_GEN

#include <string>

#endif

namespace BruxAPI {

// Main
void wait(int seconds); // Doc'd
void update(); // Doc'd
std::string getOS(); // Doc'd
int getTicks(); // Doc'd
int getFPS(); // Doc'd
void setFPS(int max_fps); // Doc'd
void setWindowTitle(const std::string& title); // Doc'd
void setWindowIcon(const std::string& file); // Doc'd
int getFrames(); // Doc'd
int displayW(); // Doc'd
int displayH(); // Doc'd
std::string bruxVersion(); // Doc'd
void toggleFullScreen(); // Doc'd

} // namespace BruxAPI

#endif
