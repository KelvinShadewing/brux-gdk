#ifndef BRUX_API_INPUT_HEADER
#define BRUX_API_INPUT_HEADER

#ifndef BRUX_API_GEN

#include <string>

#endif

namespace BruxAPI {

// Input
int keyPress(int key); // Doc'd
int keyDown(int key); // Doc'd
int keyRelease(int key); // Doc'd
int anyKeyPress(); // Doc'd
int mouseDown(int button); // Doc'd
int mousePress(int button); // Doc'd
int mouseRelease(int button); // Doc'd
int mouseX(); // Doc'd
int mouseY(); // Doc'd
bool getQuit(); // Doc'd
int joyCount(); // Doc'd
std::string joyName(int i); // Doc'd
int joyX(int i); // Doc'd
int joyY(int i); // Doc'd
int joyZ(int i); // Doc'd
int joyH(int i); // Doc'd
int joyV(int i); // Doc'd
int joyR(int i); // Doc'd
int joyL(int i); // Doc'd
int joyAxis(int i, int j); // Doc'd
bool joyHatDown(int i, int d); // Doc'd
bool joyHatPress(int i, int d); // Doc'd
bool joyHatRelease(int i, int d); // Doc'd
int joyButtonPress(int i, int b); // Doc'd
int joyButtonDown(int i, int b); // Doc'd
int joyButtonRelease(int i, int b); // Doc'd
int joyButtonAny(int p); // Doc'd
int joyAxisPress(int p, int a, int d); // Doc'd
int joyAxisRelease(int p, int a, int d); // Doc'd
std::string keyString(); // Doc'd
int mouseWheelX(); // Doc'd
int mouseWheelY(); // Doc'd

} // namespace BruxAPI

#endif
