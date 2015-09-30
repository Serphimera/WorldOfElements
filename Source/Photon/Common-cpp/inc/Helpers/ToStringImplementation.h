/* Exit Games Common - C++ Client Lib
 * Copyright (C) 2004-2015 by Exit Games GmbH. All rights reserved.
 * http://www.exitgames.com
 * mailto:developer@exitgames.com
 */

#pragma once

#include "Common-cpp/inc/Helpers/ObjectToStringConverter.h"
#include "Common-cpp/inc/Helpers/PrimitiveToStringConverter.h"

namespace ExitGames
{
	namespace Common
	{
		namespace Helpers
		{
			template<bool, typename Etype>
			struct ToStringImplementation
			{
				static ObjectToStringConverter<Etype> converter;
			};

			template<bool condition, typename Etype>
			struct ToStringImplementation<condition, Etype*>
			{
				static ObjectToStringConverter<Etype*> converter;
			};

			template<typename Etype>
			struct ToStringImplementation<true, Etype>
			{
				static PrimitiveToStringConverter<Etype> converter;
			};

			template<typename Etype>
			struct ToStringImplementation<true, Etype*>
			{
				static PrimitiveToStringConverter<Etype*> converter;
			};
		}
	}
}