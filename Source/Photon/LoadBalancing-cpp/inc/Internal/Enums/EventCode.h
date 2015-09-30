/* Exit Games Photon LoadBalancing - C++ Client Lib
 * Copyright (C) 2004-2015 by Exit Games GmbH. All rights reserved.
 * http://www.exitgames.com
 * mailto:developer@exitgames.com
 */

#pragma once

#include "Photon-cpp/inc/PhotonPeer.h"
#include "../../../../Photon-cpp/inc/Enums/EventCode.h"

namespace ExitGames
{
	namespace LoadBalancing
	{
		namespace Internal
		{
			namespace EventCode
			{
				static const nByte JOIN                = Lite::EventCode::JOIN;
				static const nByte LEAVE               = Lite::EventCode::LEAVE;
				static const nByte PROPERTIES_CHANGED  = Lite::EventCode::PROPERTIES_CHANGED;
				static const nByte CACHE_SLICE_CHANGED = 250;
				static const nByte ROOM_LIST           = 230;
				static const nByte ROOM_LIST_UPDATE    = 229;
				static const nByte APP_STATS           = 226;
				static const nByte LOBBY_STATS         = 224;
			};
		}
	}
}