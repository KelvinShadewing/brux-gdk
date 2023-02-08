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
| FILE I/O SOURCE |
\*===============*/

#include <physfs.h>

#include <filesystem>

#include "brux/main.hpp"
#include "brux/global.hpp"
#include "brux/fileio.hpp"

/* Initalize a PhysicsFS error. */
PhysFSError::PhysFSError(const std::string& message, const std::string& action) throw() :
	m_message()
{
	const PHYSFS_ErrorCode code = PHYSFS_getLastErrorCode();
	m_message = message + ": PHYSFS_" + action + " failed: " +
							PHYSFS_getErrorByCode(code) + " (" + std::to_string(code) + ")";
}

/** File system initialization/destruction. **/

void xyFSInit() {
	if (!PHYSFS_init(NULL))
		throw PhysFSError("Cannot initialize PhysicsFS", "init");
};

void xyFSDeinit() {
	if (!PHYSFS_deinit())
		throw PhysFSError("Cannot properly de-initialize PhysicsFS", "deinit");
};


/** General file system management functions. **/

void xyFSMount(const std::string& dir, const std::string& mountpoint, bool prepend) {
	if (!PHYSFS_mount(dir.c_str(), mountpoint.c_str(), !prepend))
		throw PhysFSError("Cannot mount '" + dir + "' to \"" + mountpoint + "\"", "mount");
};

void xyFSUnmount(const std::string& dir) {
	if (!PHYSFS_unmount(dir.c_str()))
		throw PhysFSError("Cannot unmount '" + dir + "'", "unmount");
};


std::string xyGetDir() {
	// Get the current working directory.
	return getcwd(0, 0);
}

std::string xyGetWriteDir() {
	const char* write_dir = PHYSFS_getWriteDir();
	if (write_dir == NULL)
		return "";
	else
		return write_dir;
};

std::string xyGetPrefDir(const std::string& org, const std::string& app) {
	const char* dir = PHYSFS_getPrefDir(org.c_str(), app.c_str());
	if (dir == NULL)
		throw PhysFSError("Error getting user-and-app specific directory", "getPrefDir");

	return dir;
};

void xySetWriteDir(const std::string& dir) {
	// If there is a current write directory, unmount it.
	const std::string write_dir = xyGetWriteDir();
	if (!write_dir.empty())
	{
		try {
			xyFSUnmount(write_dir);
		}
		catch (const std::exception& err) {
			std::stringstream out;
			out << "Error unmounting current write directory: " << err.what();
			throw std::runtime_error(out.str());
		}
	}

	if (!PHYSFS_setWriteDir(dir.c_str()))
		throw PhysFSError("Error setting '" + dir + "' directory as write directory", "setWriteDir");

	// Mount and prepend the write directory to the root of the search path.
	try {
		xyFSMount(dir, "/", true);
	}
	catch (const std::exception& err) {
		std::stringstream out;
		out << "Error mounting write directory: " << err.what();
		throw std::runtime_error(out.str());
	}
};


void xyCreateDir(const std::string& name) {
	if (!PHYSFS_mkdir(name.c_str()))
		throw PhysFSError("Could not create directory '" + name + "'", "mkdir");
}

std::string xyFileRead(const std::string& file)
{
	// Check if the file exists.
	if (!xyFileExists(file))
		throw std::runtime_error("File '" + file + "' doesn't exist.");

	PHYSFS_file* handle = PHYSFS_openRead(file.c_str());
	const int length = PHYSFS_fileLength(handle);

	char* buffer = new char[length + 1];
	buffer[length] = 0; // Terminate string at the end.
	if (PHYSFS_readBytes(handle, buffer, length) <= 0)
		throw PhysFSError("Cannot read any data from file '" + file + "'", "readBytes");

	// Copy the result and delete the pointer.
	const std::string result = buffer;
	delete[] buffer;

	PHYSFS_close(handle);
	return result;
};

void xyFileWrite(const std::string& file, const std::string& data)
{
	// If the full path to the file's directory isn't available, create it.
	xyCreateDir(std::filesystem::path(file).parent_path().string());

	PHYSFS_file* handle = PHYSFS_openWrite(file.c_str());
	const int length = data.size();

	const char* buffer = data.c_str();
	if (PHYSFS_writeBytes(handle, buffer, length) < length)
		throw PhysFSError("Cannot write all data to file '" + file + "'", "writeBytes");

	PHYSFS_close(handle);
};

void xyFileAppend(const std::string& file, const std::string& data)
{
	// If the file currently exists, read its data.
	std::string file_data;
	if (xyFileExists(file))
		file_data = xyFileRead(file);

	// Write old and new data.
	xyFileWrite(file, file_data + data);
};

bool xyFileExists(const std::string& file) {
	return PHYSFS_exists(file.c_str());
};

bool xyLegacyFileExists(const std::string& file) {
	// This function should not be exposed, because it searches beyond PhysicsFS's search path.
	// Only used for checking if the initial Squirrel file exists.

	struct stat buff;
	return stat(file.c_str(), &buff) != -1;
}

void xyFileDelete(const std::string& name)
{
	// If a directory is provided, delete all files inside of it.
	if (xyIsDirectory(name)) {
		std::filesystem::path dir_path = name;
		const std::vector<std::string> files = xyListDirectory(name);
		for (const std::string& file : files) {
			try {
				// Delete files/folders by providing their path, relative to the directory.
				xyFileDelete((dir_path / std::filesystem::path(file)).string());
			}
			catch (const std::exception& err) {
				throw PhysFSError("Could not delete file or directory '" + file + "', contained inside of the directory '" +
						name + "', which is being deleted: \"" + err.what() + "\"", "delete");
			}
		}
	}

	// Delete the file/directory.
	if (!PHYSFS_delete(name.c_str()))
		throw PhysFSError("Could not delete file or directory '" + name + "'", "delete");
};


bool xyIsDirectory(const std::string& name) {
	// Get file/directory stats.
	PHYSFS_Stat stat;
	PHYSFS_stat(name.c_str(), &stat);

	return stat.filetype == PHYSFS_FILETYPE_DIRECTORY;
}

std::vector<std::string> xyListDirectory(const std::string& dir) {
	std::vector<std::string> result;

	// Read files and append to array.
	char **rc = PHYSFS_enumerateFiles(dir.c_str());
	if (rc == NULL) {
		std::stringstream err;
		err << "Error enumerating files in directory '" << dir << "'";
		throw PhysFSError(err.str(), "enumerateFiles");
	}
	char **i;

	for (i = rc; *i != NULL; i++)
		result.push_back(*i);

	PHYSFS_freeList(rc);
	return result;
}


/** JSON encoding/decoding. **/

// Credit to Nova Storm for the JSON encoding and decoding functions

void sqDecodeJSONTable(HSQUIRRELVM v, cJSON* item) {
	if (!item) return;

	while (item) {
		if (item->str)
			sq_pushstring(v, item->str, -1);

		switch (item->type) {
			case cJSON_False:
				sq_pushbool(v, SQFalse);
				break;
			case cJSON_True:
				sq_pushbool(v, SQTrue);
				break;
			case cJSON_NULL:
				sq_pushnull(v);
				break;
			case cJSON_Number:
				if (item->valueint == item->valuedouble)
					sq_pushinteger(v, item->valueint);
				else
					sq_pushfloat(v, item->valuedouble);
				break;
			case cJSON_String:
				sq_pushstring(v, item->valuestring, -1);
				break;
			case cJSON_Array:
				sq_newarray(v, 0);
				sqDecodeJSONTable(v, item->child);
				break;
			case cJSON_Object:
				sq_newtable(v);
				sqDecodeJSONTable(v, item->child);
				break;
		}

		if (item->str)
			sq_newslot(v, -3, SQFalse);
		else
			sq_arrayappend(v, -2);

		item = item->next;
	}
};

void sqDecodeJSON(HSQUIRRELVM v, const char* str) {
	if (str[0] != '{' && str[0] != '[') {
		if (!strcmp(str, "true"))
			sq_pushbool(v, SQTrue);
		else if (!strcmp(str, "false"))
			sq_pushbool(v, SQFalse);
		else if (std::isdigit(str[0]) || (str[0] == '-' && std::isdigit(str[1])))
			sq_pushinteger(v, strtol(str, NULL, 0));
		else
			sq_pushstring(v, str, -1);
		return;
	}

	cJSON* root = cJSON_Parse(str);
	if (!root || !root->child) {
		sq_pushnull(v);
		return;
	}
	sq_newtable(v);
	sqDecodeJSONTable(v, root->child);
	cJSON_Delete(root);
	return;
}
