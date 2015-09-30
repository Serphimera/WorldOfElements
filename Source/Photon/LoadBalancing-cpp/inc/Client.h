/* Exit Games Photon LoadBalancing - C++ Client Lib
 * Copyright (C) 2004-2015 by Exit Games GmbH. All rights reserved.
 * http://www.exitgames.com
 * mailto:developer@exitgames.com
 */

#pragma once

#include "Photon-cpp/inc/Enums/ConnectionProtocol.h"
#include "LoadBalancing-cpp/inc/FriendInfo.h"
#include "LoadBalancing-cpp/inc/Listener.h"
#include "LoadBalancing-cpp/inc/LobbyStatsRequest.h"
#include "LoadBalancing-cpp/inc/LobbyStatsResponse.h"
#include "LoadBalancing-cpp/inc/MutablePlayer.h"
#include "LoadBalancing-cpp/inc/MutableRoom.h"
#include "LoadBalancing-cpp/inc/Enums/LobbyType.h"
#include "LoadBalancing-cpp/inc/Enums/MatchmakingMode.h"
#include "LoadBalancing-cpp/inc/Enums/ServerType.h"

namespace ExitGames
{
	namespace LoadBalancing
	{
		class Client : protected Photon::PhotonListener
		{
		public:
			Client(LoadBalancing::Listener& listener, const Common::JString& applicationID, const Common::JString& appVersion, const Common::JString& username, nByte connectionProtocol=Photon::ConnectionProtocol::UDP, AuthenticationValues authenticationValues=AuthenticationValues(), bool autoLobbyStats=false, bool useDefaultRegion=true);
			virtual ~Client(void);

			virtual bool connect(const Common::JString& serverAddress=NAMESERVER, nByte serverType=ServerType::NAME_SERVER);
			virtual void disconnect(void);

			virtual void service(bool dispatchIncomingCommands=true);
			virtual void serviceBasic(void);
			virtual bool opCustom(const Photon::OperationRequest& operationRequest, bool sendReliable, nByte channelID=0, bool encrypt=false);
			virtual bool sendOutgoingCommands(void);
			virtual bool sendAcksOnly(void);
			virtual bool dispatchIncomingCommands(void);
			virtual bool establishEncryption(void);
			virtual void fetchServerTimestamp(void);
			virtual void resetTrafficStats(void);
			virtual void resetTrafficStatsMaximumCounters(void);
			virtual Common::JString vitalStatsToString(bool all) const;

			virtual bool opJoinLobby(const Common::JString& lobbyName=Common::JString(), nByte lobbyType=LobbyType::DEFAULT);
			virtual bool opLeaveLobby(void);
			virtual bool opCreateRoom(const Common::JString& gameID, bool isVisible=true, bool isOpen=true, nByte maxPlayers=0, const Common::Hashtable& customRoomProperties=Common::Hashtable(), const Common::JVector<Common::JString>& propsListedInLobby=Common::JVector<Common::JString>(), const Common::JString& lobbyName=Common::JString(), nByte lobbyType=LobbyType::DEFAULT, int playerTtl=0, int emptyRoomTtl=0);
			virtual bool opJoinRoom(const Common::JString& gameID, bool createIfNotExists=false, int playerNumber=0, int cacheSliceIndex=0, int playerTtl=0, int emptyRoomTtl=0);
			virtual bool opJoinRandomRoom(const Common::Hashtable& customRoomProperties=Common::Hashtable(), nByte maxPlayers=0, nByte matchmakingMode=MatchmakingMode::FILL_ROOM, const Common::JString& lobbyName=Common::JString(), nByte lobbyType=LobbyType::DEFAULT, const Common::JString& sqlLobbyFilter=Common::JString());
			virtual bool opLeaveRoom(bool willComeBack=false);
			template<typename Ftype> typename Common::Helpers::EnableIf<!Common::Helpers::ConfirmAllowed<Ftype>::dimensions, bool>::type opRaiseEvent(bool reliable, Ftype parameters, nByte eventCode, nByte channelID=0, nByte eventCaching=Lite::EventCache::DO_NOT_CACHE, const int* targetPlayers=NULL, short numTargetPlayers=0, nByte receiverGroup=Lite::ReceiverGroup::OTHERS, nByte interestGroup=0, bool forwardToWebhook=false, int cacheSliceIndex=0)
			{
				return mPeer.opRaiseEvent(reliable, parameters, eventCode, channelID, eventCaching, targetPlayers, numTargetPlayers, receiverGroup, interestGroup, forwardToWebhook, cacheSliceIndex);
			}
			template<typename Ftype> typename Common::Helpers::EnableIf<Common::Helpers::ConfirmAllowed<Ftype>::dimensions==1, bool>::type opRaiseEvent(bool reliable, Ftype pParameterArray, typename Common::Helpers::ArrayLengthType<Ftype>::type arrSize, nByte eventCode, nByte channelID=0, nByte eventCaching=Lite::EventCache::DO_NOT_CACHE, const int* targetPlayers=NULL, short numTargetPlayers=0, nByte receiverGroup=Lite::ReceiverGroup::OTHERS, nByte interestGroup=0, bool forwardToWebhook=false, int cacheSliceIndex=0)
			{
				return mPeer.opRaiseEvent(reliable, pParameterArray, arrSize, eventCode, channelID, eventCaching, targetPlayers, numTargetPlayers, receiverGroup, interestGroup, forwardToWebhook, cacheSliceIndex);
			}
			template<typename Ftype> typename Common::Helpers::EnableIf<(Common::Helpers::ConfirmAllowed<Ftype>::dimensions>1), bool>::type opRaiseEvent(bool reliable, Ftype pParameterArray, const short* pArrSizes, nByte eventCode, nByte channelID=0, nByte eventCaching=Lite::EventCache::DO_NOT_CACHE, const int* targetPlayers=NULL, short numTargetPlayers=0, nByte receiverGroup=Lite::ReceiverGroup::OTHERS, nByte interestGroup=0, bool forwardToWebhook=false, int cacheSliceIndex=0)
			{
				return mPeer.opRaiseEvent(reliable, pParameterArray, pArrSizes, eventCode, channelID, eventCaching, targetPlayers, numTargetPlayers, receiverGroup, interestGroup, forwardToWebhook, cacheSliceIndex);
			}
			virtual bool opFindFriends(const Common::JString* friendsToFind, short numFriendsToFind);
			virtual bool opLobbyStats(const Common::JVector<LoadBalancing::LobbyStatsRequest>& lobbiesToQuery=Common::JVector<LoadBalancing::LobbyStatsRequest>());
			virtual bool opChangeGroups(const Common::JVector<nByte>* pGroupsToRemove, const Common::JVector<nByte>* pGroupsToAdd);
			virtual bool opCustomAuthenticationSendNextStepData(const AuthenticationValues& authenticationValues);
			virtual bool opWebRpc(const Common::JString& uriPath, const Common::Object& parameters);

			virtual bool selectRegion(const Common::JString& selectedRegion);

			int getServerTimeOffset(void) const;
			int getServerTime(void) const;
			int getBytesOut(void) const;
			int getBytesIn(void) const;
			int getByteCountCurrentDispatch(void) const;
			int getByteCountLastOperation(void) const;
			int getSentCountAllowance(void) const;
			void setSentCountAllowance(int setSentCountAllowance);
			int getTimePingInterval(void) const;
			void setTimePingInterval(int setTimePingInterval);
			int getRoundTripTime(void) const;
			int getRoundTripTimeVariance(void) const;
			int getTimestampOfLastSocketReceive(void) const;
			int getDebugOutputLevel(void) const;
			bool setDebugOutputLevel(int debugLevel);
			int getIncomingReliableCommandsCount(void) const;
			short getPeerId(void) const;
			int getDisconnectTimeout(void) const;
			void setDisconnectTimeout(int disconnectTimeout);
			int getQueuedIncomingCommands(void) const;
			int getQueuedOutgoingCommands(void) const;
			bool getIsEncryptionAvailable(void) const;
			int getResentReliableCommands(void) const;
			int getLimitOfUnreliableCommands(void) const;
			void setLimitOfUnreliableCommands(int value);
			bool getCrcEnabled(void) const;
			void setCrcEnabled(bool crcEnabled);
			int getPacketLossByCrc(void) const;
			bool getTrafficStatsEnabled(void) const;
			void setTrafficStatsEnabled(bool trafficStatsEnabled);
			int getTrafficStatsElapsedMs(void) const;
			const Photon::TrafficStats& getTrafficStatsIncoming(void) const;
			const Photon::TrafficStats& getTrafficStatsOutgoing(void) const;
			const Photon::TrafficStatsGameLevel& getTrafficStatsGameLevel(void) const;
			nByte getQuickResendAttempts(void);
			void setQuickResendAttempts(nByte quickResendAttempts);

			static short getPeerCount(void);

			int getState(void) const;
			const Common::JString& getMasterserverAddress(void) const;
			int getCountPlayersIngame(void) const;
			int getCountGamesRunning(void) const;
			int getCountPlayersOnline(void) const;
			MutableRoom& getCurrentlyJoinedRoom(void);
			const Common::JVector<Room*>& getRoomList(void) const;
			const Common::JVector<Common::JString>& getRoomNameList(void) const;
			bool getIsInRoom(void) const;
			bool getIsInGameRoom(void) const;
			bool getIsInLobby(void) const;
			bool getAutoJoinLobby(void) const;
			void setAutoJoinLobby(bool onConnect);
			MutablePlayer& getLocalPlayer(void);
			const Common::JVector<FriendInfo>& getFriendList(void);
			int getFriendListAge(void);
			int getDisconnectedCause(void);
		private:
			virtual bool opGetRegions(bool encrypted, const Common::JString& appID);
			virtual bool opSetPropertiesOfPlayer(int playerNr, const Common::Hashtable& properties);
			virtual bool opSetPropertiesOfRoom(const Common::Hashtable& properties, bool webForward=false);

			virtual Room* createRoom(const Common::JString& name, const Common::Hashtable& properties);
			virtual void destroyRoom(const Room* pRoom) const;
			virtual MutablePlayerFactory* getMutablePlayerFactory(void) const;
			virtual MutableRoomFactory* getMutableRoomFactory(void) const;

			// From Photon::PhotonListener
			virtual void onOperationResponse(const Photon::OperationResponse& operationResponse);
			virtual void onStatusChanged(int statusCode);
			virtual void onEvent(const Photon::EventData& eventData);
			virtual void debugReturn(int debugLevel, const Common::JString& string);

			void readoutProperties(Common::Hashtable& roomProperties, Common::Hashtable& playerProperties, bool multiplePlayers, int targetPlayerNr);
			void handleConnectionFlowError(int oldState, int errorCode, const Common::JString& errorString);
			void onConnectToMasterFinished(bool comingFromGameserver);
			MutablePlayer* createMutablePlayer(int number, const Common::Hashtable& properties);
			void destroyMutablePlayer(const MutablePlayer* pPlayer) const;
			MutableRoom* createMutableRoom(const Common::JString& name, const Common::Hashtable& properties, const Common::JVector<Common::JString>& propsListedInLobby, int playerTtl, int emptyRoomTtl);
			void destroyMutableRoom(const MutableRoom* pRoom) const;

			bool getIsOnGameServer(void) const;

			Peer mPeer;
			Listener& mListener;
			Common::Logger mLogger;
			Common::JString mGameserver;
			Common::JString mAppVersion;
			Common::JString mRoomName;
			Common::JString mAppID;
			int mPeerCount;
			int mRoomCount;
			int mMasterPeerCount;
			nByte mLastJoinType;
			nByte mLastLobbyJoinType;
			bool mLastJoinCreateIfNotExists;
			int mLastJoinPlayerNumber;
			int mLastCacheSliceIndex;
			MutableRoom* mpCurrentlyJoinedRoom;
			Common::JVector<Room*> mRoomList;
			Common::JVector<Common::JString> mRoomNameList;
			int mCachedErrorCodeFromGameServer;
			Common::JString mCachedErrorStringFromGameServer;
			bool mAutoJoinLobby;
			MutablePlayer* mpLocalPlayer;
			Common::JVector<FriendInfo> mFriendList;
			Common::JVector<Common::JString> mLastFindFriendsRequest;
			int mFriendListTimestamp;
			bool mIsFetchingFriendList;
			Common::JVector<LobbyStatsRequest> mLobbyStatsRequestList;
			int mState;
			AuthenticationValues mAuthenticationValues;
			bool mAutoLobbyStats;
			MutablePlayerFactory* mpMutablePlayerFactory;
			MutableRoomFactory* mpMutableRoomFactory;
			int mDisconnectedCause;
			Common::JString mSelectedRegion;
			const bool M_USE_DEFAULT_REGION;
			Common::JString mMasterserver;
			const nByte M_CONNECTION_PROTOCOL;

			static const Common::JString NAMESERVER;

			friend class MutablePlayer;
			friend class MutableRoom;
		};
	}
}