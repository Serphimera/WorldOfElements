/* Exit Games Photon - C++ Client Lib
 * Copyright (C) 2004-2015 by Exit Games GmbH. All rights reserved.
 * http://www.exitgames.com
 * mailto:developer@exitgames.com
 */

#pragma once

#include "Photon-cpp/inc/PhotonPeer.h"
#include "Photon-cpp/inc/Enums/EventCode.h"
#include "Photon-cpp/inc/Enums/EventCache.h"
#include "Photon-cpp/inc/Enums/EventKey.h"
#include "Photon-cpp/inc/Enums/OperationCode.h"
#include "Photon-cpp/inc/Enums/ParameterCode.h"
#include "Photon-cpp/inc/Enums/ReceiverGroup.h"
#include "Photon-cpp/inc/Enums/ConnectionProtocol.h"

class EGObjCLitePeer;

namespace ExitGames
{
	namespace Lite
	{
		class LitePeer : public Photon::PhotonPeer
		{
		public:
			LitePeer(Photon::PhotonListener& listener, nByte connectionProtocol = Photon::ConnectionProtocol::UDP);
			virtual ~LitePeer(void);
			template<typename Ftype> typename Common::Helpers::EnableIf<!Common::Helpers::ConfirmAllowed<Ftype>::dimensions, bool>::type opRaiseEvent(bool reliable, Ftype parameters, nByte eventCode, nByte channelID=0, nByte eventCaching=Lite::EventCache::DO_NOT_CACHE, const int* targetPlayers=NULL, short numTargetPlayers=0, nByte receiverGroup=Lite::ReceiverGroup::OTHERS, nByte interestGroup=0)
			{
				return opRaiseEvent(reliable, Common::Helpers::ValueToObject::get(parameters), eventCode, channelID, eventCaching, targetPlayers, numTargetPlayers, receiverGroup, interestGroup);
			}
			template<typename Ftype> typename Common::Helpers::EnableIf<Common::Helpers::ConfirmAllowed<Ftype>::dimensions==1, bool>::type opRaiseEvent(bool reliable, Ftype pParameterArray, typename Common::Helpers::ArrayLengthType<Ftype>::type arrSize, nByte eventCode, nByte channelID=0, nByte eventCaching=Lite::EventCache::DO_NOT_CACHE, const int* targetPlayers=NULL, short numTargetPlayers=0, nByte receiverGroup=Lite::ReceiverGroup::OTHERS, nByte interestGroup=0)
			{
				return opRaiseEvent(reliable, Common::Helpers::ValueToObject::get(pParameterArray, arrSize), eventCode, channelID, eventCaching, targetPlayers, numTargetPlayers, receiverGroup, interestGroup);
			}
			template<typename Ftype> typename Common::Helpers::EnableIf<(Common::Helpers::ConfirmAllowed<Ftype>::dimensions>1), bool>::type opRaiseEvent(bool reliable, Ftype pParameterArray, const short* pArrSizes, nByte eventCode, nByte channelID=0, nByte eventCaching=Lite::EventCache::DO_NOT_CACHE, const int* targetPlayers=NULL, short numTargetPlayers=0, nByte receiverGroup=Lite::ReceiverGroup::OTHERS, nByte interestGroup=0)
			{
				return opRaiseEvent(reliable, Common::Helpers::ValueToObject::get(pParameterArray, pArrSizes), eventCode, channelID, eventCaching, targetPlayers, numTargetPlayers, receiverGroup, interestGroup);
			}
			virtual bool opJoin(const Common::JString& gameId, const Common::Hashtable& gameProperties=Common::Hashtable(), const Common::Hashtable& actorProperties=Common::Hashtable(), bool broadcastActorProperties=false);
			virtual bool opLeave(void);
			virtual bool opChangeGroups(const Common::JVector<nByte>* pGroupsToRemove, const Common::JVector<nByte>* pGroupsToAdd);
			virtual bool opSetPropertiesOfActor(int actorNr, const Common::Hashtable& properties, bool broadcast, nByte channelID=0);
			virtual bool opSetPropertiesOfGame(const Common::Hashtable& properties, bool broadcast, nByte channelID=0);
			virtual bool opGetProperties(nByte channelID=0);
			virtual bool opGetPropertiesOfActor(const Common::JString* properties, short numProperties, const int* actorNrList=NULL, short numActors=0, nByte channelID=0);
			virtual bool opGetPropertiesOfActor(const nByte* properties, short numProperties, const int* actorNrList=NULL, short numActors=0, nByte channelID=0);
			virtual bool opGetPropertiesOfGame(const Common::JString* properties, short numProperties, nByte channelID=0);
			virtual bool opGetPropertiesOfGame(const nByte* properties, short numProperties, nByte channelID=0);
		protected:
			virtual bool opRaiseEvent(bool reliable, const Common::Object& parameters, nByte eventCode, nByte channelID=0, nByte eventCaching=Lite::EventCache::DO_NOT_CACHE, const int* targetPlayers=NULL, short numTargetPlayers=0, nByte receiverGroup=Lite::ReceiverGroup::OTHERS, nByte interestGroup=0);
		private:
			static const int PROP_NONE = 0x00;
			static const int PROP_GAME = 0x01;
			static const int PROP_ACTOR = 0x02;
			static const int PROP_GAME_AND_ACTOR = PROP_GAME|PROP_ACTOR;

			friend class ::EGObjCLitePeer;
		};
	}
}