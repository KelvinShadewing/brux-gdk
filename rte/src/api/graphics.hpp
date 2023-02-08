#ifndef BRUX_API_GRAPHICS_HEADER
#define BRUX_API_GRAPHICS_HEADER

#ifndef BRUX_API_GEN

#include <string>

#endif

namespace BruxAPI {

// Graphics
void clearScreen(); // Doc'd
void setDrawTarget(int tex); // Doc'd
int getDrawTarget(); // Doc'd
void resetDrawTarget();
void drawImage(int img, float x, float y); // Doc'd
void drawImageEx(int img, float x, float y, float a, int f, float w, float h, float c);
void setDrawColor(int color); // Doc'd
int loadImage(const std::string& file); // Doc'd
int loadImageKey(const std::string& file, int key); // Doc'd
void setBackgroundColor(int color); // Doc'd
void setScaling(float scale);
void setScalingFilter(int hint); // Doc'd
void setResolution(int w, int h); // Doc'd
int screenW(); // Doc'd
int screenH(); // Doc'd
int windowW();
int windowH();
int newTexture(int w, int h); // Doc'd
void textureSetBlendMode(int texture, int blend); // Doc'd

} // namespace BruxAPI

#endif
