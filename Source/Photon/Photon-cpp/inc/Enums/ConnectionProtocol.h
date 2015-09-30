/* Exit Games Photon - C++ Client Lib
 * Copyright (C) 2004-2015 by Exit Games GmbH. All rights reserved.
 * http://www.exitgames.com
 * mailto:developer@exitgames.com
 */

#pragma once

#include "Common-cpp/inc/Common.h"

namespace ExitGames
{
	namespace Photon
	{
		/** These are the options that can be used as underlying transport protocol.*/
		namespace ConnectionProtocol
		{
			static const nByte UDP = 0; ///<Use UDP to connect to Photon, which allows you to send operations reliable or unreliable on demand.
			static const nByte TCP = 1; ///<Use TCP to connect to Photon.
		}
		/** @file */
	}
}