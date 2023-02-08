#ifndef BRUX_API_TEXT_HEADER
#define BRUX_API_TEXT_HEADER

#ifndef BRUX_API_GEN

#include <string>

#include <squirrel.h>

#endif

namespace BruxAPI {

// Text
int newFont(int i, int c, int t, bool m, int k); // Doc'd
void drawText(int f, int x, int y, const std::string& s); // Doc'd
SQInteger chint(HSQUIRRELVM v, int i); // Doc'd

} // namespace BruxAPI

#endif
