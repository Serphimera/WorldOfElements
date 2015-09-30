/* Exit Games Photon LoadBalancing - C++ Client Lib
 * Copyright (C) 2004-2015 by Exit Games GmbH. All rights reserved.
 * http://www.exitgames.com
 * mailto:developer@exitgames.com
 */

#pragma once

#include "Common-cpp/inc/Common.h"
#include "LoadBalancing-cpp/inc/Enums/LobbyType.h"

namespace ExitGames
{
	namespace LoadBalancing
	{
		class LobbyStatsResponse : public Common::Base
		{
		public:
			using Common::ToString::toString;

			Common::JString getName(void) const;
			nByte getType(void) const;
			int getPeerCount(void) const;
			int getRoomCount(void) const;

			virtual Common::JString& toString(Common::JString& retStr, bool withTypes=false) const;
		private:
			LobbyStatsResponse(const Common::JString& name=Common::JString(), nByte type=LobbyType::DEFAULT, int peerCount=0, int roomCount=0);

			Common::JString mName;
			nByte mType;
			int mPeerCount;
			int mRoomCount;

			friend class Client;
		};
	}
}