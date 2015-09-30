/* Exit Games Common - C++ Client Lib
 * Copyright (C) 2004-2015 by Exit Games GmbH. All rights reserved.
 * http://www.exitgames.com
 * mailto:developer@exitgames.com
 */

#pragma once

#include "Common-cpp/inc/DictionaryBase.h"

namespace ExitGames
{
	namespace Common
	{
		template<typename EKeyType, typename EValueType>
		class Dictionary : public DictionaryBase
		{
		public:
			Dictionary(void);
			~Dictionary(void);

			Dictionary(const Dictionary<EKeyType, EValueType>& toCopy);
			Dictionary& operator=(const Dictionary<EKeyType, EValueType>& toCopy);

			bool operator==(const Dictionary<EKeyType, EValueType>& toCompare) const;
			bool operator!=(const Dictionary<EKeyType, EValueType>& toCompare) const;
			const EValueType& operator[](unsigned int index) const;
			EValueType& operator[](unsigned int index);

			const nByte* getKeyTypes(void) const;
			const nByte* getValueTypes(void) const;
			const unsigned int* getValueDimensions(void) const;
			void put(const Dictionary<EKeyType, EValueType>& src);
			void put(const EKeyType& key, const EValueType& val);
			void put(const EKeyType& key);
			void put(const EKeyType& key, const EValueType& pVal, typename Common::Helpers::ArrayLengthType<EValueType>::type size);
			void put(const EKeyType& key, const EValueType& pVal, const short* sizes);
			const EValueType* getValue(const EKeyType& key) const;
			JVector<EKeyType> getKeys(void) const;
			void remove(const EKeyType& key);
			bool contains(const EKeyType& key) const;
		protected:
			virtual Dictionary<EKeyType, EValueType>& assign(const DictionaryBase&);
		private:
			typedef DictionaryBase super;

			bool compare(const DictionaryBase &toCompare) const;
			DictionaryBase* copy(short amount) const;

			static bool mStaticMembersHaveBeenInitialized;

			template<typename EType> struct NestingDepth{static const unsigned int nestingDepth = 0;};
			template<template<typename, typename> class EType, typename ENestedKeyType, typename ENestedValueType> struct NestingDepth<EType<ENestedKeyType, ENestedValueType> >{static const unsigned int nestingDepth = NestingDepth<ENestedValueType>::nestingDepth+1;};

			static const unsigned int M_NESTING_DEPTH = NestingDepth<Dictionary<EKeyType, EValueType> >::nestingDepth;
			static nByte mpKeyTypes[M_NESTING_DEPTH+DEBUG_RELEASE(1, 0)]; // one unused byte at the end in debug config for easier debugging
			static nByte mpValueTypes[M_NESTING_DEPTH+DEBUG_RELEASE(1, 0)];
			static unsigned int mpValueDimensions[M_NESTING_DEPTH+DEBUG_RELEASE(1, 0)];

			template<typename EType, typename ERPType = typename Helpers::RemovePointer<EType>::type> struct NestedInfos{static void fillArrays(nByte keyTypes[M_NESTING_DEPTH], nByte valueTypes[M_NESTING_DEPTH], unsigned int valueDimensions[M_NESTING_DEPTH], unsigned int recursionDepth=0);};
			template<typename EType, template<typename, typename> class ETemplate, typename ENestedKeyType, typename ENestedValueType> struct NestedInfos<EType, ETemplate<ENestedKeyType, ENestedValueType> >{static void fillArrays(nByte keyTypes[M_NESTING_DEPTH], nByte valueTypes[M_NESTING_DEPTH], unsigned int valueDimensions[M_NESTING_DEPTH], unsigned int recursionDepth=0);};
		};

		template<typename EKeyType, typename EValueType> bool Dictionary<EKeyType, EValueType>::mStaticMembersHaveBeenInitialized = false;
		template<typename EKeyType, typename EValueType> nByte Dictionary<EKeyType, EValueType>::mpKeyTypes[M_NESTING_DEPTH+DEBUG_RELEASE(1, 0)];
		template<typename EKeyType, typename EValueType> nByte Dictionary<EKeyType, EValueType>::mpValueTypes[M_NESTING_DEPTH+DEBUG_RELEASE(1, 0)];
		template<typename EKeyType, typename EValueType> unsigned int Dictionary<EKeyType, EValueType>::mpValueDimensions[M_NESTING_DEPTH+DEBUG_RELEASE(1, 0)];

		/** @file */

		/** @class Dictionary
		   The Dictionary class template together with the Hashtable class is one of the two main container classes for objects to be
		   transmitted over Photon when using the C++ Client.
		   @details
		   This class implements the well-known concept of a container structure storing an arbitrary number of key/value-pairs.

		   In contrast to a Hashtable, the types of both the keys and also the values in a Dictionary have to be the same for all
		   entries.
		   This takes flexibility, but it also improves type safety and means, that the type infos only have to be stored twice 
		   for the whole Dictionary (once for the key and once for the value), while in a Hashtable they have to be stored twice per
		   entry.
		   Therefor with Dictionaries transferring the same amount of key-value pairs will cause less traffic than with Hashtables.

		   Please have a look at the @link Datatypes Table of Datatypes\endlink for a list of types, that are supported as keys and as
		   values.

		   Please refer to the documentation for put() and getValue() to see how to store and access data in a Dictionary.
		   @sa
		   put(), getValue(), KeyObject, ValueObject, Hashtable, DictionaryBase */

		/** @copydoc Hashtable::Hashtable(void) */ 
		template<typename EKeyType, typename EValueType>
		Dictionary<EKeyType, EValueType>::Dictionary(void)
		{
			if(!mStaticMembersHaveBeenInitialized)
			{
				NestedInfos<Dictionary<EKeyType, EValueType> >::fillArrays(mpKeyTypes, mpValueTypes, mpValueDimensions);
				mStaticMembersHaveBeenInitialized = true;
			}
		}

		/** @copydoc DictionaryBase::~DictionaryBase(void) */
		template<typename EKeyType, typename EValueType>
		Dictionary<EKeyType, EValueType>::~Dictionary(void)
		{
		}

		/** @copydoc DictionaryBase::DictionaryBase(const DictionaryBase&) */
		template<typename EKeyType, typename EValueType>
		Dictionary<EKeyType, EValueType>::Dictionary(const Dictionary<EKeyType, EValueType>& toCopy) : DictionaryBase(toCopy)
		{
		}

		/** @copydoc DictionaryBase::operator=() */
		template<typename EKeyType, typename EValueType>
		Dictionary<EKeyType, EValueType>& Dictionary<EKeyType, EValueType>::operator=(const Dictionary<EKeyType, EValueType>& toCopy)
		{
			return assign(toCopy);
		}

		/** @copydoc DictionaryBase::operator==() */
		template<typename EKeyType, typename EValueType>
		bool Dictionary<EKeyType, EValueType>::operator==(const Dictionary<EKeyType, EValueType>& toCompare) const
		{
			return this->compare(toCompare);
		}

		/** @copydoc DictionaryBase::operator!=() */
		template<typename EKeyType, typename EValueType>
		bool Dictionary<EKeyType, EValueType>::operator!=(const Dictionary<EKeyType, EValueType>& toCompare) const
		{
			return !this->compare(toCompare);
		}

		/** @copydoc Hashtable::operator[]() */
		template<typename EKeyType, typename EValueType>
		const EValueType& Dictionary<EKeyType, EValueType>::operator[](unsigned int index) const
		{
			return getElementAt(index, *reinterpret_cast<EValueType*>(NULL));
		}

		/** @copydoc Hashtable::operator[]() */
		template<typename EKeyType, typename EValueType>
		EValueType& Dictionary<EKeyType, EValueType>::operator[](unsigned int index)
		{
			return getElementAt(index, *reinterpret_cast<EValueType*>(NULL));
		}

		template<typename EKeyType, typename EValueType>
		Dictionary<EKeyType, EValueType>& Dictionary<EKeyType, EValueType>::assign(const DictionaryBase& toCopy)
		{
			super::assign(toCopy);
			return *this;
		}

		/** @copydoc Hashtable::put(const Hashtable&) */
		template<typename EKeyType, typename EValueType>
		void Dictionary<EKeyType, EValueType>::put(const Dictionary<EKeyType, EValueType>& src)
		{
			super::put(src.getHashtable());
		}

		/** @copydoc Hashtable::put(const FKeyType&,const FValueType&) */
		template<typename EKeyType, typename EValueType>
		void Dictionary<EKeyType, EValueType>::put(const EKeyType& key, const EValueType& val)
		{
			super::put(key, val);
		}

		/** @copydoc Hashtable::put(const FKeyType&) */
		template<typename EKeyType, typename EValueType>
		void Dictionary<EKeyType, EValueType>::put(const EKeyType& key)
		{
			COMPILE_TIME_ASSERT2_TRUE_MSG((Helpers::IsDerivedFrom<EValueType, Object>::Is), ERROR_OMITTING_THE_VALUE_IS_NOT_SUPPORTED_FOR_DICTIONARIES_EXCEPT_WHEN_THE_VALUE_TYPE_IS_OBJECT);
			super::put(key);
		}

		/** @copydoc Hashtable::put(const FKeyType&,FValueType,short) */
		template<typename EKeyType, typename EValueType>
		void Dictionary<EKeyType, EValueType>::put(const EKeyType& key, const EValueType& pVal, typename Common::Helpers::ArrayLengthType<EValueType>::type size)
		{
			super::put(key, pVal, size);
		}

		/** @copydoc Hashtable::put(const FKeyType&,FValueType,const short* const) */
		template<typename EKeyType, typename EValueType>
		void Dictionary<EKeyType, EValueType>::put(const EKeyType& key, const EValueType& pVal, const short* const sizes)
		{
			super::put(key, pVal, sizes);
		}

		/** @copydoc Hashtable::getValue() */
		template<typename EKeyType, typename EValueType>
		const EValueType* Dictionary<EKeyType, EValueType>::getValue(const EKeyType& key) const
		{
			return super::getValue(key, *reinterpret_cast<EValueType*>(NULL));
		}

		/** @copydoc Hashtable::getKeys() */
		template<typename EKeyType, typename EValueType>
		JVector<EKeyType> Dictionary<EKeyType, EValueType>::getKeys(void) const
		{
			return super::getKeys<EKeyType>();
		}

		/** @copydoc Hashtable::remove() */
		template<typename EKeyType, typename EValueType>
		void Dictionary<EKeyType, EValueType>::remove(const EKeyType& key)
		{
			mHashtable.remove(key);
		}

		/** @copydoc Hashtable::contains() */
		template<typename EKeyType, typename EValueType>
		bool Dictionary<EKeyType, EValueType>::contains(const EKeyType& key) const
		{
			return getHashtable().contains(key);
		}

		template<typename EKeyType, typename EValueType>
		const nByte* Dictionary<EKeyType, EValueType>::getKeyTypes(void) const
		{
			return mpKeyTypes;
		}

		template<typename EKeyType, typename EValueType>
		const nByte* Dictionary<EKeyType, EValueType>::getValueTypes(void) const
		{
			return mpValueTypes;
		}

		template<typename EKeyType, typename EValueType>
		const unsigned int* Dictionary<EKeyType, EValueType>::getValueDimensions(void) const
		{
			return mpValueDimensions;
		}

		template<typename EKeyType, typename EValueType>
		bool Dictionary<EKeyType, EValueType>::compare(const DictionaryBase &toCompare) const
		{
			return getHashtable() == toCompare.getHashtable();
		}

		template<typename EKeyType, typename EValueType>
		DictionaryBase* Dictionary<EKeyType, EValueType>::copy(short amount) const
		{
			DictionaryBase* pRetVal = MemoryManagement::allocateArray<Dictionary<EKeyType, EValueType> >(amount);
			for(short i=0; i<amount; i++)
				pRetVal[i] = this[i];
			return pRetVal;
		}

		template<typename EKeyType, typename EValueType> template<typename EType, typename ERPType>
		void Dictionary<EKeyType, EValueType>::NestedInfos<EType, ERPType>::fillArrays(nByte[M_NESTING_DEPTH], nByte[M_NESTING_DEPTH], unsigned int[M_NESTING_DEPTH], unsigned int)
		{
		}

		template<typename EKeyType, typename EValueType> template<typename EType, template<typename, typename> class ETemplate, typename ENestedKeyType, typename ENestedValueType> 
		void Dictionary<EKeyType, EValueType>::NestedInfos<EType, ETemplate<ENestedKeyType, ENestedValueType> >::fillArrays(nByte keyTypes[M_NESTING_DEPTH], nByte valueTypes[M_NESTING_DEPTH], unsigned int valueDimensions[M_NESTING_DEPTH], unsigned int recursionDepth)
		{
			keyTypes[recursionDepth] = Helpers::ConfirmAllowedKey<ENestedKeyType>::typeName;
			valueTypes[recursionDepth] = Helpers::ConfirmAllowed<ENestedValueType>::typeName;
			valueDimensions[recursionDepth] = Helpers::ConfirmAllowed<ENestedValueType>::dimensions;
			if(recursionDepth < M_NESTING_DEPTH)
				NestedInfos<ENestedValueType>::fillArrays(keyTypes, valueTypes, valueDimensions, recursionDepth+1);
		}
	}
}