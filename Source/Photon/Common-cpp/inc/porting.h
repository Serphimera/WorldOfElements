/* Exit Games Common - C++ Client Lib
 * Copyright (C) 2004-2015 by Exit Games GmbH. All rights reserved.
 * http://www.exitgames.com
 * mailto:developer@exitgames.com
 */

#pragma once

#include "Common-cpp/inc/defines.h"

#if defined _EG_WINDOWS_PLATFORM
#	if defined _EG_WINDOWS_PLATFORM
#		define WIN32_LEAN_AND_MEAN
#		if _WIN32_WINNT < 0x0500
#			undef _WIN32_WINNT
#		endif
#		ifndef _WIN32_WINNT
#			define _WIN32_WINNT 0x0500
#		endif
#		include <process.h>
#		include <mbstring.h>
#	endif
#	include <tchar.h>
#	include <assert.h>
#	include <winsock2.h>
#	include <windows.h>
#	include <time.h>
#	include <ws2tcpip.h>
#	include <wininet.h>
#	include <urlmon.h>
#	include <string.h>
#elif defined _EG_UNIX_PLATFORM
#	include <pthread.h>
#	if defined _EG_APPLE_PLATFORM
#		include <AvailabilityMacros.h>
#		import <CoreFoundation/CFString.h>
#		import <CoreFoundation/CoreFoundation.h>
#		include <sys/time.h>
#	elif defined _EG_BLACKBERRY_PLATFORM
#		include <sys/time.h>
#		include <iconv.h>
#		include <limits.h>
#	elif defined _EG_MARMALADE_PLATFORM
#		include <limits.h>
#	elif defined _EG_ANDROID_PLATFORM
#		include <sys/time.h>
#		include <sys/limits.h>
#	elif defined _EG_PS3_PLATFORM
#		include <limits.h>
#		include <time.h>
#		include <assert.h>
#	endif
#endif