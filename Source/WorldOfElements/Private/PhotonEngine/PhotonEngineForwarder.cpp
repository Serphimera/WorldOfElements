// Copyright 2015 Nethersoft (Sebastian Kenter). All rights reserved.

#include "WorldOfElements.h"
#include "PhotonEngineForwarder.h"

void UPhotonEngineForwarder::ForwardOperationResponse(FPhotonOperationResponse FResponse)
{
    if (ForwardPhotonOperationResponse.IsBound())
    {
        ForwardPhotonOperationResponse.Broadcast(FResponse);
    }
}

void UPhotonEngineForwarder::ForwardStatusChanged(int statusCode)
{
    if (ForwardPhotonStatusChange.IsBound())
    {
        ForwardPhotonStatusChange.Broadcast(statusCode);
    }
}

void UPhotonEngineForwarder::ForwardEvent(FPhotonEventData FPhotonEvent)
{
    if (ForwardPhotonEvent.IsBound())
    {
        ForwardPhotonEvent.Broadcast(FPhotonEvent);
    }
}

void UPhotonEngineForwarder::ForwardDebugReturn(FPhotonDebugData FDebugData)
{
    if (ForwardPhotonDebugReturn.IsBound())
    {
        ForwardPhotonDebugReturn.Broadcast(FDebugData);
    }
}