// Copyright 2015 Nethersoft (Sebastian Kenter). All rights reserved.

#include "WorldOfElements.h"
#include "WoEGameInstance.h"

void UWoEGameInstance::Init()
{
    FPhotonEngineClient = NewObject<UPhotonEngineClient>();

    Super::Init();
}

void UWoEGameInstance::Shutdown()
{
    Super::Shutdown();
}

void UWoEGameInstance::PhotonCallService(bool bDispatchIncomingCommands)
{
    if (FPhotonEngineClient)
    {
        FPhotonEngineClient->PhotonCallService(bDispatchIncomingCommands);
    }
}

void UWoEGameInstance::PhotonSendOperationRequest(int32 FPhotonOperationCode, TArray<FPhotonOperationRequestParameters> FRequestParameters, int32 FChannelId)
{
    if (FPhotonEngineClient)
    {
        FPhotonEngineClient->PhotonSendOperationRequest(FPhotonOperationCode, FRequestParameters, FChannelId);
    }
}

UPhotonEngineForwarder* UWoEGameInstance::GetPhotonForwarder()
{
    return FPhotonEngineClient->GetPhotonForwarder();
}