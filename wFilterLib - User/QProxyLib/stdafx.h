// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
//

#pragma once

#include "targetver.h"
#define _CRT_SECURE_NO_WARNINGS
#define _SILENCE_CXX17_CODECVT_HEADER_DEPRECATION_WARNING
#define WIN32_LEAN_AND_MEAN             // Exclude rarely-used stuff from Windows headers
// Windows Header Files
#include <windows.h>

#pragma warning( disable : 4307 ) // warning C4307: '*': integral constant overflow
#pragma warning( disable : 4244 ) // warning C4244: '=': conversion possible loss of data
#pragma warning( disable : 4996 ) // stupid json error when you try and stream a file to json so we can use it
#define NOMINMAX
#include <WinSock2.h>
#include <windows.h>
#include <winuser.h>
#include <intrin.h>
#include <cstdint>
#include <string>
#include <stdio.h>
#include <array>
#include <vector>
#include <map>
#include <memory>
#include <sstream>
#include <fstream>
#include <iostream>
#include <iomanip>
#include <cctype>
#include <random>
#include <thread>
#include <chrono>
#include <future>
#include <winsock.h>
#include <utility>
#include "VMProtectSDK.h"
#include <stdio.h>
#include <wchar.h>
#include <regex>

// reference additional headers your program requires here
