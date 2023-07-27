//  Brux - File I/O API
//  Copyright (C) 2016 KelvinShadewing
//                2023 Vankata453
//
//  This program is free software: you can redistribute it and/or modify
//  it under the terms of the GNU Affero General Public License as published by
//  the Free Software Foundation, either version 3 of the License, or
//  (at your option) any later version.
//
//  This program is distributed in the hope that it will be useful,
//  but WITHOUT ANY WARRANTY; without even the implied warranty of
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//  GNU Affero General Public License for more details.
//
//  You should have received a copy of the GNU Affero General Public License
//  along with this program.  If not, see <http://www.gnu.org/licenses/>.

#ifndef BRUX_API_FILEIO_HEADER
#define BRUX_API_FILEIO_HEADER

#ifndef BRUX_API_GEN

#include <string>

#include <squirrel.h>

#endif

namespace BruxAPI {

/////////////
// FILE IO //
/////////////

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
