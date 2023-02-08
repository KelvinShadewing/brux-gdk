#ifndef BRUX_API_FILEIO_HEADER
#define BRUX_API_FILEIO_HEADER

#ifndef BRUX_API_GEN

#include <string>

#include <squirrel.h>

#endif

namespace BruxAPI {

// File IO
void import(const std::string& file); // Clone of `donut()`
void donut(const std::string& file); // Doc'd
void dostr(const std::string& str); // Doc'd
void mount(const std::string& dir, const std::string& mountpoint, bool prepend); // Doc'd
void unmount(const std::string& dir); // Doc'd
std::string getdir(); // Doc'd
std::string getWriteDir(); // Doc'd
std::string getPrefDir(const std::string& org, const std::string& app); // Doc'd
void setWriteDir(const std::string& dir); // Doc'd
void createDir(const std::string& name); // Doc'd
std::string fileRead(const std::string& file); // Doc'd
void fileWrite(const std::string& file, const std::string& data); // Doc'd
void fileAppend(const std::string& file, const std::string& data); // Doc'd
bool fileExists(const std::string& file); // Doc'd
void fileDelete(const std::string& file); // Doc'd
bool isdir(const std::string& dir); // Doc'd
SQInteger lsdir(HSQUIRRELVM v, const std::string& dir); // Doc'd

} // namespace BruxAPI

#endif
