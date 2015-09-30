/* Exit Games Photon LoadBalancing - C++ Client Lib
 * Copyright (C) 2004-2015 by Exit Games GmbH. All rights reserved.
 * http://www.exitgames.com
 * mailto:developer@exitgames.com
 */

#pragma once

#include "Common-cpp/inc/Common.h"
#include "LoadBalancing-cpp/inc/Enums/CustomAuthenticationType.h"

namespace ExitGames
{
	namespace LoadBalancing
	{
		namespace Internal
		{
			class AuthenticationValuesSecretSetter;
		}

		class AuthenticationValues : Common::Base
		{
		public:
			AuthenticationValues(nByte type=CustomAuthenticationType::NONE, const Common::JString& parameters=Common::JString(), const Common::JVector<nByte>& data=Common::JVector<nByte>());
			AuthenticationValues(const Common::JVector<nByte>& data);
			AuthenticationValues(const Common::JString& username, const Common::JString& token, const Common::JVector<nByte>& data=Common::JVector<nByte>());
			AuthenticationValues(const Common::JString& parameters, const Common::JVector<nByte>& data=Common::JVector<nByte>());

			nByte getType(void) const;
			const Common::JString& getParameters(void) const;
			const Common::JVector<nByte>& getData(void) const;
			const Common::JString& getSecret(void) const;
			
			virtual Common::JString& toString(Common::JString& retStr, bool withTypes=false) const;
		private:
			void setSecret(const Common::JString& secret);

			nByte mType;
			Common::JString mParameters;
			Common::JVector<nByte> mData;
			Common::JString mSecret;

			friend class Internal::AuthenticationValuesSecretSetter;
		};
	}
}