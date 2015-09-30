// Copyright 2015 Nethersoft (Sebastian Kenter). All rights reserved.

#pragma once

#include "Object.h"
#include "PhotonEngineDefinitions.h"
#include "PhotonEngineForwarder.generated.h"

/**
 * 
 */
UCLASS(Blueprintable, Category = PhotonForwarder)
class WORLDOFELEMENTS_API UPhotonEngineForwarder : public UObject
{
	GENERATED_BODY()
	
public:
		
    void ForwardOperationResponse(FPhotonOperationResponse FResponse);
    void ForwardStatusChanged(int statusCode);
    void ForwardEvent(FPhotonEventData FPhotonEvent);
    void ForwardDebugReturn(FPhotonDebugData FDebugData);

    DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnPhotonOperationResponseReceived, FPhotonOperationResponse, OperationResponseData);
    FOnPhotonOperationResponseReceived ForwardPhotonOperationResponse;

    DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnPhotonEventReceived, FPhotonEventData, OperationEventData);
    FOnPhotonEventReceived ForwardPhotonEvent;

    DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnPhotonStatusChangeReceived, int32, OperationStatusData);
    FOnPhotonStatusChangeReceived ForwardPhotonStatusChange;

    DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnPhotonDebugReturnReceived, FPhotonDebugData, OperationDebugData);
    FOnPhotonDebugReturnReceived ForwardPhotonDebugReturn;
};
