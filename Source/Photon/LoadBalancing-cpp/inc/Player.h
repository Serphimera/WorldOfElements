/* Exit Games Photon LoadBalancing - C++ Client Lib
 * Copyright (C) 2004-2015 by Exit Games GmbH. All rights reserved.
 * http://www.exitgames.com
 * mailto:developer@exitgames.com
 */

#pragma once

#include "LoadBalancing-cpp/inc/Internal/PlayerFactory.h"
#include "LoadBalancing-cpp/inc/Internal/PlayerPropertiesCacher.h"

namespace ExitGames
{
	namespace LoadBalancing
	{
		class Player : public Common::Base
		{
		public:
			using Common::ToString::toString;

			virtual ~Player(void);

			Player(const Player& toCopy);
			virtual Player& operator=(const Player& toCopy);

			int getNumber(void) const;
			const Common::JString& getName() const;
			const Common::Hashtable& getCustomProperties() const;
			bool getIsInactive(void) const;
			bool operator==(const Player& player) const;
			virtual Common::JString& toString(Common::JString& retStr, bool withTypes=false) const;
			virtual Common::JString toString(bool withTypes, bool withCustomProperties) const;
		protected:
			Player(int number, const Common::Hashtable& properties, const MutableRoom* pRoom);

			virtual bool getIsMutable(void) const;

			virtual Player& assign(const Player& toCopy);
			virtual void setIsInactive(bool);
			virtual void cacheProperties(const Common::Hashtable& properties);
			virtual Common::JString payloadToString(bool withTypes, bool withCustomProperties=false) const;

			int mNumber;
			Common::JString mName;
			Common::Hashtable mCustomProperties;
			const MutableRoom* mpRoom;
			bool mIsInactive;
		private:
			Player(void);

			friend class Internal::PlayerFactory;
			friend class Internal::PlayerPropertiesCacher;
		};
	}
}