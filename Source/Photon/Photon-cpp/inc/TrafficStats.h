/* Exit Games Photon - C++ Client Lib
 * Copyright (C) 2004-2015 by Exit Games GmbH. All rights reserved.
 * http://www.exitgames.com
 * mailto:developer@exitgames.com
 */

#pragma once

#include "Common-cpp/inc/Common.h"

namespace ExitGames
{
	namespace Photon
	{
		class TrafficStats
		{
		public:
			int getPackageHeaderSize(void) const;
			int getReliableCommandCount(void) const;
			int getUnreliableCommandCount(void) const;
			int getFragmentCommandCount(void) const;
			int getControlCommandCount(void) const;
			int getTotalPacketCount(void) const;
			int getTotalCommandsInPackets(void) const;
			int getReliableCommandBytes(void) const;
			int getUnreliableCommandBytes(void) const;
			int getFragmentCommandBytes(void) const;
			int getControlCommandBytes(void) const;
			int getTotalCommandCount(void) const;
			int getTotalCommandBytes(void) const;
			int getTotalPacketBytes(void) const;
			int getTimestampOfLastAck(void) const;
			int getTimestampOfLastReliableCommand(void) const;

			virtual Common::JString toString(void) const;
		protected:
			TrafficStats(int packageHeaderSize);

			int mPackageHeaderSize;
			int mReliableCommandCount;
			int mUnreliableCommandCount;
			int mFragmentCommandCount;
			int mControlCommandCount;
			int mTotalPacketCount;
			int mTotalCommandsInPackets;
			int mReliableCommandBytes;
			int mUnreliableCommandBytes;
			int mFragmentCommandBytes;
			int mControlCommandBytes;
			int mTimestampOfLastAck;
			int mTimestampOfLastReliableCommand;
		};
	}
}