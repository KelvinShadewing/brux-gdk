//  Brux - File I/O
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

/*===============*\
| FILE I/O HEADER |
\*===============*/

#ifndef _FILEIO_H_
#define _FILEIO_H_

#include <string>
#include <vector>

/* A class that takes the last PhysicsFS error and converts it to a readable message. */
class PhysFSError final : public std::exception
{
private:
	std::string m_message;

public:
	PhysFSError(const std::string& message, const std::string& action) throw();

	const char* what() const throw() { return m_message.c_str(); }
};

/** File system initialization/destruction. **/
void xyFSInit();
void xyFSDeinit();

/** General file system management functions. **/
void xyFSMount(const std::string& dir, const std::string& mountpoint, bool prepend);
void xyFSUnmount(const std::string& dir);

std::string xyGetDir();
std::string xyGetWriteDir();
std::string xyGetPrefDir(const std::string& org, const std::string& app);
void xySetWriteDir(const std::string& dir);

void xyCreateDir(const std::string& name);
std::string xyFileRead(const std::string& file);
void xyFileWrite(const std::string& file, const std::string& data);
void xyFileAppend(const std::string& file, const std::string& data);
bool xyFileExists(const std::string& file);
bool xyLegacyFileExists(const std::string& file);
void xyFileDelete(const std::string& name);

bool xyIsDirectory(const std::string& name);
std::vector<std::string> xyListDirectory(const std::string& dir);

/** JSON encoding/decoding. **/
void sqDecodeJSONTable(HSQUIRRELVM v, cJSON *Item);
SQInteger sqDecodeJSON(HSQUIRRELVM v);

#endif
