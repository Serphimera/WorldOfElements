/* Exit Games Photon LoadBalancing - C++ Client Lib
 * Copyright (C) 2004-2015 by Exit Games GmbH. All rights reserved.
 * http://www.exitgames.com
 * mailto:developer@exitgames.com
 */

#pragma once

#include "Photon-cpp/inc/PhotonPeer.h"
#include "../../../../Photon-cpp/inc/Enums/ParameterCode.h"

namespace ExitGames
{
	namespace LoadBalancing
	{
		namespace Internal
		{
			namespace ParameterCode
			{
				static const nByte ROOM_NAME                          = Lite::ParameterCode::GAMEID;
				static const nByte PLAYERNR                           = Lite::ParameterCode::ACTORNR;
				static const nByte TARGET_PLAYERNR                    = Lite::ParameterCode::TARGET_ACTORNR;
				static const nByte PLAYER_LIST                        = Lite::ParameterCode::ACTOR_LIST;
				static const nByte PROPERTIES                         = Lite::ParameterCode::PROPERTIES;
				static const nByte BROADCAST                          = Lite::ParameterCode::BROADCAST;
				static const nByte PLAYER_PROPERTIES                  = Lite::ParameterCode::ACTOR_PROPERTIES;
				static const nByte ROOM_PROPERTIES                    = Lite::ParameterCode::GAME_PROPERTIES;
				static const nByte RECEIVER_GROUP                     = Lite::ParameterCode::RECEIVER_GROUP;
				static const nByte CACHE                              = Lite::ParameterCode::CACHE;
				static const nByte DATA                               = Lite::ParameterCode::DATA;
				static const nByte CODE                               = Lite::ParameterCode::CODE;
				static const nByte CLEANUP_CACHE_ON_LEAVE             = 241;
				static const nByte GROUP                              = Lite::ParameterCode::GROUP;
				static const nByte REMOVE                             = Lite::ParameterCode::REMOVE;
				static const nByte ADD                                = Lite::ParameterCode::ADD;
				static const nByte EMPTY_ROOM_TTL                     = 236;
				static const nByte PLAYER_TTL                         = 235;
				static const nByte EVENT_FORWARD                      = 234;
				static const nByte IS_COMING_BACK                     = 233;
				static const nByte IS_INACTIVE                        = 233; //intentionally same as previous
				static const nByte CHECK_USER_ON_JOIN                 = 232;
				static const nByte ADDRESS                            = 230;
				static const nByte PEER_COUNT                         = 229;
				static const nByte ROOM_COUNT                         = 228;
				static const nByte MASTER_PEER_COUNT                  = 227;
				static const nByte USER_ID                            = 225;
				static const nByte APPLICATION_ID                     = 224;
				static const nByte MATCHMAKING_TYPE                   = 223;
				static const nByte ROOM_LIST                          = 222;
				static const nByte SECRET                             = 221;
				static const nByte APP_VERSION                        = 220;
				static const nByte CLIENT_AUTHENTICATION_TYPE         = 217;
				static const nByte CLIENT_AUTHENTICATION_PARAMETERS   = 216;
				static const nByte CREATE_IF_NOT_EXISTS               = 215;
				static const nByte CLIENT_AUTHENTICATION_DATA         = 214;
				static const nByte LOBBY_NAME                         = 213;
				static const nByte LOBBY_TYPE                         = 212;
				static const nByte LOBBY_STATS                        = 211;
				static const nByte REGION                             = 210;
				static const nByte URI_PATH                           = 209;
				static const nByte RPC_CALL_PARAMS                    = 208;
				static const nByte RPC_CALL_RET_CODE                  = 207;
				static const nByte RPC_CALL_RET_MESSAGE               = 206;
				static const nByte CACHE_SLICE_INDEX                  = 205;
				static const nByte FIND_FRIENDS_RESPONSE_ROOM_ID_LIST =   2;
				static const nByte FIND_FRIENDS_RESPONSE_ONLINE_LIST  =   1;
				static const nByte FIND_FRIENDS_REQUEST_LIST          =   1;
			};
		}
	}
}