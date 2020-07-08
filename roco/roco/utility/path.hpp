#pragma once

#ifndef _ROCO_UTILITY_PATH_HPP_
#define _ROCO_UTILITY_PATH_HPP_

#include "../roco_ns.h"

#include <windows.h>

#ifdef WIN32
#include <io.h>
#include <direct.h>
#else
#include <unistd.h>
#include <sys/stat.h>
#endif

#include <stdint.h>
#include <string>

#define MAX_PATH_LEN 256

#ifdef WIN32
#define ACCESS(fileName, accessMode) _access(fileName, accessMode)
#define MKDIR(path) _mkdir(path)
#define PATH_DELIMITER '\\'
#else
#define ACCESS(fileName, accessMode) access(fileName, accessMode)
#define MKDIR(path) mkdir(path, S_IRWXU|S_IRWXG|S_IROTH|S_IXOTH)
#define PATH_DELIMITER '/'
#endif

_ROCO_BEGIN

class Path
{
public:
	static std::string pwd() noexcept
	{
		char dir[MAX_PATH];
		::GetCurrentDirectoryA(MAX_PATH, dir);
		return std::string(dir);
	}
};

_ROCO_END

#endif // _ROCO_UTILITY_PATH_HPP_