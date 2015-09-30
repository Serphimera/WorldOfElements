/* Exit Games Photon LoadBalancing - C++ Client Lib
 * Copyright (C) 2004-2015 by Exit Games GmbH. All rights reserved.
 * http://www.exitgames.com
 * mailto:developer@exitgames.com
 */

#pragma once

#include "LoadBalancing-cpp/inc/Player.h"
#include "LoadBalancing-cpp/inc/Internal/MutablePlayerFactory.h"

namespace ExitGames
{
	namespace LoadBalancing
	{
		class MutablePlayer : public Player
		{
		public:
			virtual ~MutablePlayer(void);

			MutablePlayer(const MutablePlayer& toCopy);
			virtual MutablePlayer& operator=(const Player& toCopy);

			void setName(const Common::JString& name);
			bool getIsMasterClient(void) const;

			void mergeCustomProperties(const Common::Hashtable& customProperties);
			template<typename ktype, typename vtype> void addCustomProperty(const ktype& key, const vtype& value);
			void addCustomProperties(const Common::Hashtable& customProperties);
			template<typename ktype> void removeCustomProperty(const ktype& key);
			template<typename ktype> void removeCustomProperties(const ktype* keys, unsigned int count);
		protected:
			MutablePlayer(int number, const Common::Hashtable& properties, const MutableRoom* pRoom, Client* pClient);

			virtual bool getIsMutable(void) const;

			virtual MutablePlayer& assign(const Player& toCopy);
		private:
			typedef Player super;

			Client* mLoadBalancingClient;

			friend class MutablePlayerFactory;
		};



		template<typename ktype, typename vtype> void MutablePlayer::addCustomProperty(const ktype& key, const vtype& value)
		{
			Common::Hashtable hash;
			hash.put(key, value);
			addCustomProperties(hash);
		}

		template<typename ktype> void MutablePlayer::removeCustomProperty(const ktype& key)
		{
			removeCustomProperties(&key, 1);
		}

		template<typename ktype> void MutablePlayer::removeCustomProperties(const ktype* keys, unsigned int count)
		{
			Common::Hashtable hash;
			for(unsigned int i=0; i<count; i++)
				hash.put(keys[i]);
			mergeCustomProperties(hash);
		}
	}
}