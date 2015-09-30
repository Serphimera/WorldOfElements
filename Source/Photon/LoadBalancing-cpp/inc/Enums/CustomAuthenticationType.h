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
		/** Options for optional "Custom Authentication" services used with Photon. Used by OpAuthenticate after connecting to Photon.*/
		namespace CustomAuthenticationType
		{
			static const nByte CUSTOM   = 0; ///<Use a custom authentification service. Currently the only implemented option.
			static const nByte STEAM    = 1; ///<Authenticates users by their Steam Account. Set auth values accordingly!
			static const nByte FACEBOOK = 2; ///<Authenticates users by their Facebook Account. Set auth values accordingly!
			static const nByte NONE     = UCHAR_MAX; ///<Disables custom authentification.
		}
		/** @file */
	}
}