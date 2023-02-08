#ifndef BRUX_API_MATHS_HEADER
#define BRUX_API_MATHS_HEADER

#ifndef BRUX_API_GEN

#include <string>

#endif

namespace BruxAPI {

// Maths
float randFloat(float a); // Doc'd
int randInt(int a); // Doc'd
float distance2(float x1, float y1, float x2, float y2); // Doc'd
bool inDistance2(float x1, float y1, float x2, float y2, float d);
float distance3(float x1, float y1, float z1, float x2, float y2, float z2);
float wrap(float x, float mx, float mn); // Doc'd
int floor(float f); // Doc'd
int ceil(float f); // Doc'd
int round(float f); // Doc'd
float pointAngle(float x1, float y1, float x2, float y2); // Doc'd
float abs(float f); // Doc'd
float lendirX(float l, float d); // Doc'd
float lendirY(float l, float d); // Doc'd
std::string binstr(int i); // Doc'd

} // namespace BruxAPI

#endif
