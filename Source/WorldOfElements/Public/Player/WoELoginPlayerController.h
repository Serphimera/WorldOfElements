// Copyright 2015 Nethersoft (Sebastian Kenter). All rights reserved.

#pragma once

#include "GameFramework/PlayerController.h"
#include "PhotonEngineDefinitions.h"
#include "WoELoginPlayerController.generated.h"

/**
 * 
 */
UCLASS(Blueprintable)
class WORLDOFELEMENTS_API AWoELoginPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:

    virtual void BeginPlay() override;

    UFUNCTION(BlueprintImplementableEvent, Category = PhotonEvents)
    void HandleOperationResponse(FPhotonOperationResponse FOperationResponse);
	
    UFUNCTION(BlueprintImplementableEvent, Category = PhotonEvents)
    void HandleEvent(FPhotonEventData FPEvenData);

    UFUNCTION(BlueprintImplementableEvent, Category = PhotonEvents)
    void HandleStatusChanged(int32 FStatusCode);

    UFUNCTION(BlueprintImplementableEvent, Category = PhotonEvents)
    void HandleDebugReturn(FPhotonDebugData FDebugData);
};
