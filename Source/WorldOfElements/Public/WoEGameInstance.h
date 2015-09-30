// Copyright 2015 Nethersoft (Sebastian Kenter). All rights reserved.

#pragma once

#include "Engine/GameInstance.h"
#include "PhotonEngineClient.h"
#include "WoEGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class WORLDOFELEMENTS_API UWoEGameInstance : public UGameInstance
{
    GENERATED_BODY()

public:
	
    virtual void Init() override;
    virtual void Shutdown() override;

    UFUNCTION(BlueprintCallable, Category = PhotonCore)
    void PhotonCallService(bool bDispatchIncomingCommands);

    UFUNCTION(BlueprintCallable, Category = PhotonCore)
    void PhotonSendOperationRequest(int32 FPhotonOperationCode, TArray<FPhotonOperationRequestParameters> FRequestParameters, int32 FChannelId);

    UPhotonEngineForwarder* GetPhotonForwarder();

private:

    UPROPERTY()
    UPhotonEngineClient* FPhotonEngineClient;
};
