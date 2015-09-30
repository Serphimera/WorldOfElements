/* Exit Games Photon LoadBalancing - C++ Client Lib
 * Copyright (C) 2004-2015 by Exit Games GmbH. All rights reserved.
 * http://www.exitgames.com
 * mailto:developer@exitgames.com
 */

#pragma once

#include "Photon-cpp/inc/PhotonPeer.h"

namespace ExitGames
{
	namespace LoadBalancing
	{
		namespace Internal
		{
			// Photon properties, internally set by LoadBalancing (LoadBalancing builtin properties)
			namespace Properties
			{
				namespace Room
				{
					static const nByte MAX_PLAYERS           = 255;
					static const nByte IS_VISIBLE            = 254;
					static const nByte IS_OPEN               = 253;
					static const nByte PLAYER_COUNT          = 252;
					static const nByte REMOVED               = 251;
					static const nByte PROPS_LISTED_IN_LOBBY = 250;
				};
			}
		}
	}
}