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
		namespace Internal
		{
			namespace Utils
			{
				Common::Hashtable stripToCustomProperties(const Common::Hashtable& properties);
				Common::Hashtable stripKeysWithNullValues(const Common::Hashtable& orig);
			}
		}
	}
}