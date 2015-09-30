/* Exit Games Common - C++ Client Lib
 * Copyright (C) 2004-2015 by Exit Games GmbH. All rights reserved.
 * http://www.exitgames.com
 * mailto:developer@exitgames.com
 */

#pragma once

#include "Common-cpp/inc/ValueObject.h"

namespace ExitGames
{
	namespace Common
	{
		namespace Helpers
		{
			class ValueToObject
			{
			public:
				template<typename Ftype> static Object get(Ftype value);
				static Object get(Object value);
				static Object get(const char* value);
				static Object get(const wchar_t* value);
				template<unsigned int N> static Object get(const char value[N]);
				template<unsigned int N> static Object get(const wchar_t value[N]);
				static Object get(nByte* pValue, int size);
				template<typename Ftype> static Object get(Ftype* pValue, short size);
				static Object get(char** pValue, short size);
				static Object get(const char** pValue, short size);
				static Object get(wchar_t** pValue, short size);
				static Object get(const wchar_t** pValue, short size);
				template<typename Ftype> static Object get(Ftype** pValue, const short* sizes);
			private:
				template<typename Ftype> static Object stringArrayHelper(Ftype** pValue, short size);
			};



			template<typename Ftype>
			Object ValueToObject::get(Ftype value)
			{
				return ValueObject<Ftype>(value);
			}

			template<unsigned int N>
			Object ValueToObject::get(const char value[N])
			{
				return ValueToObject::get(JString(value));
			}

			template<unsigned int N>
			Object ValueToObject::get(const wchar_t value[N])
			{
				return ValueToObject::get(JString(value));
			}

			template<typename Ftype>
			Object ValueToObject::get(Ftype* pValue, short size)
			{
				return ValueObject<Ftype*>(pValue, size);
			}

			template<typename Ftype>
			Object ValueToObject::get(Ftype** pValue, const short* sizes)
			{
				return ValueObject<Ftype**>(pValue, sizes);
			}

			template<typename Ftype>
			Object ValueToObject::stringArrayHelper(Ftype** pValue, short size)
			{
				JString* pArr = MemoryManagement::allocateArray<JString>(size);
				for(short i=0; i<size; ++i)
					pArr[i] = pValue[i];
				Object retVal = ValueObject<JString*>(pArr, size);
				MemoryManagement::deallocateArray(pArr);
				return retVal;
			}
		}
	}
}