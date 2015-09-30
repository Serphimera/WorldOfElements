/* Exit Games Common - C++ Client Lib
 * Copyright (C) 2004-2015 by Exit Games GmbH. All rights reserved.
 * http://www.exitgames.com
 * mailto:developer@exitgames.com
 */

#pragma once

#include <limits.h>
#include "Common-cpp/inc/MemoryManagement/Internal/MemoryPool.h"

#if defined _EG_MARMALADE_PLATFORM && (defined EG_DEBUGGER || !defined _EG_MS_COMPILER) && defined I3D_ARCH_X86
#	define EG_DEACTIVATE_MEMORY_MANAGER
#endif

namespace ExitGames
{
	namespace Common
	{
		namespace MemoryManagement
		{
			namespace Internal
			{
				class MemoryPoolManager
				{
				public:
					MemoryPoolManager(void);
					void* alloc(size_t s);
					void dealloc(void* p);
					void* resize(void* p, size_t size);

					static MemoryPoolManager& get(void);
#ifdef EG_DEBUGGER
					unsigned long long ctr, ctr2, ctr3;
#endif
#ifndef EG_DEACTIVATE_MEMORY_MANAGER
				private:
					static const unsigned char M_POOL_COUNT = sizeof(size_t)*CHAR_BIT;
					MemoryPool mpPool[M_POOL_COUNT];
#endif
				};
			}
		}
	}
}