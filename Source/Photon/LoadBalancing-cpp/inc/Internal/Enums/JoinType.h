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
			namespace JoinType
			{
				static const nByte CREATE_ROOM         = 255;
				static const nByte JOIN_ROOM           = 254;
				static const nByte JOIN_RANDOM_ROOM    = 253;
				static const nByte AUTO_JOIN_LOBBY     = 252;
				static const nByte EXPLICIT_JOIN_LOBBY = 251;
			};
		}
	}
}