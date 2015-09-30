// Copyright 2015 Nethersoft (Sebastian Kenter). All rights reserved.

#pragma once

#include "PhotonImports.h"
#include "PhotonEngineForwarder.h"

using namespace ExitGames::Common;
using namespace ExitGames::Photon;

/**
 * 
 */
class WORLDOFELEMENTS_API PhotonEngineListener : public PhotonListener
{
public:
	// Default constructor
    PhotonEngineListener();

    // Default destructor
	~PhotonEngineListener();

    virtual void onOperationResponse(const OperationResponse& operationResponse) override;

    virtual void onStatusChanged(int statusCode) override;

    virtual void onEvent(const EventData& eventData) override;

    virtual void debugReturn(int debugLevel, const JString& string) override;

    void SetPhotonForwarder(UPhotonEngineForwarder* Forwarder);

private:

    UPhotonEngineForwarder* ActiveForwarder;
};
