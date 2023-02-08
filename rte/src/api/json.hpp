#ifndef BRUX_API_JSON_HEADER
#define BRUX_API_JSON_HEADER

#ifndef BRUX_API_GEN

#include <string>

#include <squirrel.h>

#endif

namespace BruxAPI {

// JSON
SQInteger jsonRead(HSQUIRRELVM v, const std::string& str); // Doc'd

} // namespace BruxAPI

#endif
