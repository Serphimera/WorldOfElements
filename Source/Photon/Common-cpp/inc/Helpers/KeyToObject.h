/* Exit Games Common - C++ Client Lib
 * Copyright (C) 2004-2015 by Exit Games GmbH. All rights reserved.
 * http://www.exitgames.com
 * mailto:developer@exitgames.com
 */

#pragma once

#include "Common-cpp/inc/KeyObject.h"

namespace ExitGames
{
	namespace Common
	{
		namespace Helpers
		{
			class KeyToObject
			{
			public:
				template<typename Ftype> static Object get(Ftype key);
				static Object get(Object key);
				static Object get(const char* key);
				static Object get(const wchar_t* key);
			};



			template<typename Ftype>
			Object KeyToObject::get(Ftype key)
			{
				return KeyObject<Ftype>(key);
			}
		}
	}
}