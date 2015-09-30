// Copyright 2015 Nethersoft (Sebastian Kenter). All rights reserved.

#include "WorldOfElements.h"
#include "PhotonEngineClient.h"

UPhotonEngineClient::UPhotonEngineClient(const FObjectInitializer& ObjectInitializer)
    : Super(ObjectInitializer)
{

}

void UPhotonEngineClient::PostInitProperties()
{
    FPhotonEngineForwarder = NewObject<UPhotonEngineForwarder>();

    FPhotonEngineListener = new PhotonEngineListener();

    if (!FPhotonEngineListener)
    {
        return;
    }

    FPhotonEngineListener->SetPhotonForwarder(FPhotonEngineForwarder);

    FPhotonPeer = new PhotonPeer(*FPhotonEngineListener, ConnectionProtocol::UDP);

    if (!FPhotonPeer)
    {
        return;
    }

    bPhotonIsConnecting = FPhotonPeer->connect(*ServerAddress, reinterpret_cast<nByte*>(UTF8_TO_TCHAR(*ApplicationName)));

    Super::PostInitProperties();
}

void UPhotonEngineClient::PhotonCallService(bool bDispatchIncomingCommands)
{
    if (FPhotonPeer && (bPhotonIsConnecting || bPhotonIsConnected))
    {
        FPhotonPeer->service(bDispatchIncomingCommands);
    }
}

void UPhotonEngineClient::PhotonSendOperationRequest(int32 FOperationCode, TArray<FPhotonOperationRequestParameters> FOperationParameters, int32 FChannelId)
{
    OperationRequestParameters Parameters;

    for (auto b = 0; b < FOperationParameters.Num(); b++)
    {
        Parameters.put(FOperationParameters[b].FPhotonOperationRequestParameterCode, ValueObject<JString>(*FOperationParameters[b].FPhotonOperationRequestParameterString));
    }

    OperationRequest Request(FOperationCode, Parameters);

    if (FPhotonPeer)
    {
        FPhotonPeer->opCustom(Request, bSendReliable, FChannelId, bSendEncrypted);
    }
}

void UPhotonEngineClient::PhotonSetConnectionState(bool bIsConnecting, bool bIsConnected)
{
    bPhotonIsConnecting = bIsConnecting;
    bPhotonIsConnected = bIsConnected;
}

bool UPhotonEngineClient::PhotonGetIsConnecting()
{
    return bPhotonIsConnecting;
}

bool UPhotonEngineClient::PhotonGetIsConnected()
{
    return bPhotonIsConnected;
}

UPhotonEngineForwarder* UPhotonEngineClient::GetPhotonForwarder()
{
    return FPhotonEngineForwarder;
}

void UPhotonEngineClient::SetActivePhotonForwarder(UPhotonEngineForwarder* FActivePhotonForwarder)
{
    if (FActivePhotonForwarder)
    {
        FPhotonEngineListener->SetPhotonForwarder(FActivePhotonForwarder);
    }
}