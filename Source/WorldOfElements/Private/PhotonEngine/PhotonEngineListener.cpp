// Copyright 2015 Nethersoft (Sebastian Kenter). All rights reserved.

#include "WorldOfElements.h"
#include "PhotonEngineDefinitions.h"
#include "PhotonEngineListener.h"

PhotonEngineListener::PhotonEngineListener()
{
}

PhotonEngineListener::~PhotonEngineListener()
{
}

void PhotonEngineListener::onOperationResponse(const OperationResponse& operationResponse)
{

    FPhotonOperationResponse FResponse;
    FPhotonOperationResponseParameters FResponseParameters;

    FResponse.FPhotonOperationResponseCode = operationResponse.getOperationCode();
    FResponse.FPhotonOperationResponseReturnCode = operationResponse.getReturnCode();
    FResponse.FPhotonOperationResponseDebugMessage = operationResponse.getDebugMessage().cstr();

    Hashtable Parameters = operationResponse.getParameters();

    for (uint8 b = 0; b < Parameters.getSize(); b++)
    {
        Object const* obj = Parameters.getValue(b);
        if (obj)
        {
            FResponseParameters.FPhotonOperationResponseParameterCode = b;
            FResponseParameters.FPhotonOperationResponseParameterString = ((ValueObject<JString>*)obj)->getDataCopy();
            FResponse.FPhotonResponseParameters.Add(FResponseParameters);
        }
    }

    if (ActiveForwarder)
    {
        ActiveForwarder->ForwardOperationResponse(FResponse);
    }
}

void PhotonEngineListener::onStatusChanged(int statusCode)
{
    if (ActiveForwarder)
    {
        ActiveForwarder->ForwardStatusChanged(statusCode);
    }
}

void PhotonEngineListener::onEvent(const EventData& eventData)
{

    FPhotonEventData FPhotonEvent;

    FPhotonEvent.FPhotonEventCode = eventData.getCode();

    if (ActiveForwarder)
    {
        ActiveForwarder->ForwardEvent(FPhotonEvent);
    }
}

void PhotonEngineListener::debugReturn(int debugLevel, const JString& string)
{
    FPhotonDebugData FDebugData;

    FDebugData.FPhotonDebugCode = debugLevel;
    FDebugData.FPhotonDebugMessage = string.cstr();
    
    if (ActiveForwarder)
    {
        ActiveForwarder->ForwardDebugReturn(FDebugData);
    }
}

void PhotonEngineListener::SetPhotonForwarder(UPhotonEngineForwarder* Forwarder)
{
    if (Forwarder)
    {
        ActiveForwarder = Forwarder;
    }
}