/* Exit Games Common - C++ Client Lib
* Copyright (C) 2004-2015 by Exit Games GmbH. All rights reserved.
* http://www.exitgames.com
* mailto:developer@exitgames.com
*/

#pragma once

namespace ExitGames
{
	namespace Common
	{
		namespace Helpers
		{
			template<typename T> struct RemoveConst
			{
				typedef T type;
			};

			template<typename T> struct RemoveConst<const T>
			{
				typedef T type;
			};

			template<typename T> struct RemoveConst<const T*>
			{
				typedef T* type;
			};
		}
	}
}