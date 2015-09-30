/* Exit Games Photon LoadBalancing - C++ Client Lib
 * Copyright (C) 2004-2015 by Exit Games GmbH. All rights reserved.
 * http://www.exitgames.com
 * mailto:developer@exitgames.com
 */

#pragma once

#include "Common-cpp/inc/Common.h"

namespace ExitGames
{
	namespace LoadBalancing
	{
		class FriendInfo : public Common::Base
		{
		public:
			using Common::ToString::toString;

			FriendInfo(const Common::JString& name, bool isOnline=false, const Common::JString& room=Common::JString());

			Common::JString getName(void) const;
			bool getIsOnline(void) const;
			Common::JString getRoom(void) const;
			bool getIsInRoom(void) const;

			virtual Common::JString& toString(Common::JString& retStr, bool withTypes=false) const;
		private:
			Common::JString mName;
			bool mIsOnline;
			Common::JString mRoom;
		};
	}
}