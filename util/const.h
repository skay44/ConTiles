//
// Created by Ja on 5/23/2025.
//

#ifndef CONST_H
#define CONST_H

#ifdef _WIN32
	#define PLATFORM_NAME "windows" // Windows
    #define USING_WINDOWS
#elif defined(_WIN64)
	#define PLATFORM_NAME "windows" // Windows
	#define USING_WINDOWS
#elif defined(__CYGWIN__) && !defined(_WIN32)
	#define PLATFORM_NAME "windows" // Windows (Cygwin POSIX under Microsoft Window)
	#define USING_WINDOWS
#elif defined(__ANDROID__)
	#define PLATFORM_NAME "android" // Android (implies Linux, so it must come first)
	#define USING_ANDROID
#elif defined(__linux__)
	#define PLATFORM_NAME "linux" // Debian, Ubuntu, Gentoo, Fedora, openSUSE, RedHat, Centos and other
	#define USING_LINUX
#endif

#ifdef USING_WINDOWS
	#include <windows.h>
#endif

#ifdef USING_LINUX
	#include <sys/ioctl.h>
	#include <unistd.h>
#endif

#define FILE_LENGTH 256

#endif //CONST_H

