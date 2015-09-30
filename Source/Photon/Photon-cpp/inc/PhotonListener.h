/* Exit Games Photon - C++ Client Lib
 * Copyright (C) 2004-2015 by Exit Games GmbH. All rights reserved.
 * http://www.exitgames.com
 * mailto:developer@exitgames.com
 */

#pragma once

#include "Photon-cpp/inc/OperationResponse.h"
#include "Photon-cpp/inc/EventData.h"

namespace ExitGames
{
	namespace Photon
	{
		/* The PhotonListener class defines the callback interface to allow your application to communicate with the Photon Server via the PhotonPeer class. This interface defines the following
		   callback functions:
		   <table noborder>
		   onEvent() is called every time an event is received.
		   onOperationResponse() is called in response to every operation you sent to the Photon server, carrying the Photon servers result code.
		   onStatusChanged() is called on errors and connection-state changes.
		   debugReturn() is called if a Photon related error occurs, passing an error message. This will happen e.g. if you call a PhotonPeer function with invalid parameters.
		   </table>
		   Please note that Photon will free any data passed as arguments as soon as the callback function returns, so make sure to create copies within the callback function of all data needed by
		   your application beyond the scope of the callback function.                                                                                       */
		class PhotonListener: public Common::BaseListener
		{
		public:
			virtual ~PhotonListener(void){}
			/**
			 This function gets called by the library as callback to operations in response to operations sent to the Photon Server providing the response values from the server.
			 @details
			 This callback is used as general callback for all operations. The type of an operation is identified by an operation code.
		 
			 An operation's response is summarized by the return code: an int typed code, 0 for OK or some error code defined by the application, which is defining the operation itself. The opCode
			 defines the type of operation called on Photon and in turn also the return values. They are provided as a Hashtable which contains the complete reponse of Photon, including keys for
			 operation code and return code. Each operation returns its opCode and returnCode but anything else can be defined serverside.
		 
			 @param operationResponse the @link OperationResponse\endlink                      */
			virtual void onOperationResponse(const OperationResponse& operationResponse) = 0;

			/** 
			 onStatusChanged is used to denote errors or simply state-changes of the respective PhotonPeer.
			 @details
			 State change callback
		 
			 When this function is used to signalize a state-change, the statusCode will be one of these:
			 * SC_CONNECT the connection to the Photon Server was established
			 * SC_DISCONNECT the connection was closed (due to an API-call or a timeout)
		 
			 Furthermore this function will be called by Photon to infrom about connection errors and warnings. Check PhotonConstants for a list (they start with SC_).
		 
			 @param statusCode see description                        */
			virtual void onStatusChanged(int statusCode) = 0;

			/**
			 This is the event handler function for all Events transmitted by PhotonPeer.
			 @details
			 Whenever a Photon event is sent and received, the receiving peer will be notified via this function. Please refer to @link SendingAndReceivingData Sending and receiving data\endlink for
			 more information.
		 
			 This way, an application can react on any event, based on its event code.
		 
			 The following events are reported by default:
			 EV_RT_JOIN
			 EV_RT_LEAVE
		 
			 These events are predefined and will be triggered as soon as a player has joined or has left the room in which the local player is currently active in. To transmit in-room data, define
			 your own events as needed for your application, and transmit them  using LitePeer::opRaiseEvent().
		 
		 
		 
			 All events which are raised in reaction to some player's actions (like sending data) contain the actor number of the sending player in the "parameters" Hashtable.
		 
			 If the received event has been raised by another player by calling LitePeer::opRaiseEvent(), the transmitted payload hashtable will be stored in the "parameters" hashtable of at key
			 EV_RT_KEY_DATA. Please refer to the demos for sample code.
			 @param eventData the @link EventData\endlink
			 @sa
			 @link SendingAndReceivingData Sending and receiving data\endlink, LitePeer::opRaiseEvent()*/
			virtual void onEvent(const EventData& eventData) = 0;
		};

		/** @file */
	}
}