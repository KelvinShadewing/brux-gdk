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

#include "api/fileio.hpp"

#include "brux/main.hpp"

#include "brux/fileio.hpp"
#include "brux/global.hpp"

namespace BruxAPI {

/////////////
// FILE IO //
/////////////

void import(const std::string& file) {
	donut(file);
}

void donut(const std::string& file) {
	xyPrint("Running %s...", file.c_str());
	sqstd_dofile(gvSquirrel, file.c_str(), 0, 1);
}

void require(const std::string& file) {
	gvDidError = false;

	xyPrint("Running %s...", file.c_str());
	sqstd_dofile(gvSquirrel, file.c_str(), 0, 1);

	if(gvDidError)
		xyEnd();
}

void dostr(const std::string& str) {
	SQInteger oldtop = sq_gettop(gvSquirrel);

	sq_compilebuffer(gvSquirrel, str.c_str(), static_cast<int>(str.size()) * sizeof(SQChar), "std::string", 1);
	sq_pushroottable(gvSquirrel);
	sq_call(gvSquirrel, 1, SQFalse, SQTrue);
	sq_settop(gvSquirrel, oldtop);
}

void mount(const std::string& dir, const std::string& mountpoint, bool prepend) {
	xyFSMount(dir, mountpoint, prepend);
}

void unmount(const std::string& dir) {
	xyFSUnmount(dir);
}

std::string getdir() {
	return xyGetDir();
}

std::string getWriteDir() {
	return xyGetWriteDir();
}

std::string getPrefDir(const std::string& org, const std::string& app) {
	return xyGetPrefDir(org, app);
}

void setWriteDir(const std::string& dir) {
	xySetWriteDir(dir);
}

void createDir(const std::string& name) {
	xyCreateDir(name);
}

std::string fileRead(const std::string& file) {
	if (xyFileExists(file)) {
		return xyFileRead(file);
	}

	xyPrint("WARNING: %s does not exist!", file.c_str());
	
	return "-1";
}

void fileWrite(const std::string& file, const std::string& data) {
	xyFileWrite(file, data);
}

void fileAppend(const std::string& file, const std::string& data) {
	xyFileAppend(file, data);
}

bool fileExists(const std::string& file) {
	return xyFileExists(file);
}

void fileDelete(const std::string& file) {
	xyFileDelete(file);
}

bool isdir(const std::string& dir) {
	return xyIsDirectory(dir);
}

SQInteger lsdir(HSQUIRRELVM v, const std::string& dir) {
	// Create array for results.

	sq_newarray(v, 0);

	// Append all results to the array.
	
	const std::vector<std::string> files = xyListDirectory(dir);

	for (const std::string& file: files) {
		sq_pushstring(v, file.c_str(), file.size());
		sq_arrayappend(v, -2);
	}
	
	return 1;
}

} // namespace BruxAPI
