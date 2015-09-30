/* Exit Games Photon LoadBalancing - C++ Client Lib
 * Copyright (C) 2004-2015 by Exit Games GmbH. All rights reserved.
 * http://www.exitgames.com
 * mailto:developer@exitgames.com
 */

#pragma once

#include "LoadBalancing-cpp/inc/Peer.h"
#include "LoadBalancing-cpp/inc/Player.h"
#include "LoadBalancing-cpp/inc/Room.h"
#include "LoadBalancing-cpp/inc/Internal/MutableRoomFactory.h"
#include "LoadBalancing-cpp/inc/Internal/PlayerPropertiesUpdateInformant.h"

namespace ExitGames
{
	namespace LoadBalancing
	{
		namespace Internal
		{
			class PlayerMovementInformant;
		}

		class MutableRoom : public Room
		{
		public:
			using Room::toString;

			virtual ~MutableRoom(void);

			MutableRoom(const MutableRoom& toCopy);
			virtual MutableRoom& operator=(const Room& toCopy);

			nByte getPlayerCount(void) const;
			void setMaxPlayers(nByte maxPlayers);
			void setIsOpen(bool isOpen);
			bool getIsVisible(void) const;
			void setIsVisible(bool isVisible);
			const Common::JVector<Player*>& getPlayers(void) const;
			const Player* getPlayerForNumber(int playerNumber) const;
			int getMasterClientID(void) const;
			const Common::JVector<Common::JString>& getPropsListedInLobby(void) const;
			void setPropsListedInLobby(const Common::JVector<Common::JString>& propsListedInLobby, bool webForward=false);
			int getPlayerTtl(void) const;
			int getEmptyRoomTtl(void) const;

			void mergeCustomProperties(const Common::Hashtable& customProperties, bool webForward=false);
			template<typename ktype, typename vtype> void addCustomProperty(const ktype& key, const vtype& value, bool webForward=false);
			void addCustomProperties(const Common::Hashtable& customProperties, bool webForward=false);
			template<typename ktype> void removeCustomProperty(const ktype& key, bool webForward=false);
			template<typename ktype> void removeCustomProperties(const ktype* keys, unsigned int count, bool webForward=false);
			virtual Common::JString toString(bool withTypes=false, bool withCustomProperties=false, bool withPlayers=false) const;
		protected:
			using Room::payloadToString;

			MutableRoom(const Common::JString& name, const Common::Hashtable& properties, Client* pClient, const Common::JVector<Common::JString>& propsListedInLobby, int playerTtl, int emptyRoomTtl);

			virtual bool getIsMutable(void) const;

			virtual MutableRoom& assign(const Room& toCopy);
			virtual Player* createPlayer(int number, const Common::Hashtable& properties) const;
			virtual void destroyPlayer(const Player* pPlayer) const;
			virtual Common::JString payloadToString(bool withCustomProperties=false, bool withTypes=false, bool withPlayers=false) const;
		private:
			void cacheProperties(const Common::Hashtable& properties);
			template<typename Etype> void setRoomProperty(nByte key, Etype val);

			void setPlayers(const Common::JVector<Player*>& players);
			void removeAllPlayers(void);
			void destroyAllPlayers(void);
			void addPlayer(Player& player);
			void addLocalPlayer(Player& player);
			void addPlayer(int number, const Common::Hashtable& properties);
			bool removePlayer(int number);
			Common::JVector<Player*>& getNonConstPlayers(void);

			typedef Room super;

			Client* mLoadBalancingClient;
			bool mIsVisible;
			Common::JVector<Player*> mPlayers;
			int mMasterClientID;
			Common::JVector<Common::JString> mPropsListedInLobby;
			int mLocalPlayerNumber;
			int mPlayerTtl;
			int mEmptyRoomTtl;

			friend class MutableRoomFactory;
			friend class Internal::RoomPropertiesCacher;
			friend class Internal::PlayerMovementInformant;
			friend class Internal::PlayerPropertiesUpdateInformant;
		};



		template<typename ktype, typename vtype>
		void MutableRoom::addCustomProperty(const ktype& key, const vtype& value, bool webForward)
		{
			Common::Hashtable hash;
			hash.put(key, value);
			addCustomProperties(hash, webForward);
		}

		template<typename ktype>
		void MutableRoom::removeCustomProperty(const ktype& key, bool webForward)
		{
			removeCustomProperties(&key, 1, webForward);
		}

		template<typename ktype>
		void MutableRoom::removeCustomProperties(const ktype* const keys, unsigned int count, bool webForward)
		{
			Common::Hashtable hash;
			for(unsigned int i=0; i<count; i++)
				hash.put(keys[i]);
			mergeCustomProperties(hash, webForward);
		}
	}
}