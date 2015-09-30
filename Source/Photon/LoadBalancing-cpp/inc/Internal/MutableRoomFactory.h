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
		class Client;
		class MutableRoom;
		class Peer;

		class MutableRoomFactory
		{
		protected:
			virtual ~MutableRoomFactory(void);
			virtual MutableRoom* create(const Common::JString& name, const Common::Hashtable& properties, Client* pClient, const Common::JVector<Common::JString>& propsListedInLobby, int playerTtl, int emptyRoomTtl);
			virtual void destroy(const MutableRoom* pRoom);
		private:
			friend class LoadBalancing::Client;
		};
	}
}