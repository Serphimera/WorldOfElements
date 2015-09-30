/* Exit Games Photon - C++ Client Lib
 * Copyright (C) 2004-2015 by Exit Games GmbH. All rights reserved.
 * http://www.exitgames.com
 * mailto:developer@exitgames.com
 */

#pragma once

#include "Common-cpp/inc/Common.h"

namespace ExitGames
{
	namespace Lite
	{
		namespace EventCache
		{
			static const nByte DO_NOT_CACHE                            =  0;
			static const nByte MERGE_CACHE                             =  1;
			static const nByte REPLACE_CACHE                           =  2;
			static const nByte REMOVE_CACHE                            =  3;
			static const nByte ADD_TO_ROOM_CACHE                       =  4;
			static const nByte ADD_TO_ROOM_CACHE_GLOBAL                =  5; // actor will become 0 (room owned)
			static const nByte REMOVE_FROM_ROOM_CACHE                  =  6;
			static const nByte REMOVE_FROM_ROOM_CACHE_FOR_ACTORS_LEFT  =  7; // Removes events of players who already left the room (cleaning up)
			static const nByte SLICE_INC_INDEX                         = 10; // Increment the slice index by one
			static const nByte SLICE_SET_INDEX                         = 11; // Set the slice index
			static const nByte SLICE_PURGE_INDEX                       = 12; // Delete or purge a slice index
			static const nByte SLICE_PURGE_UP_TO_INDEX                 = 13; // Purge all cache slices up to the index (inclusive)
		}
		/** @file */
	}
}