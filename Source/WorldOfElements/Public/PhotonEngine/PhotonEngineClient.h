// Copyright 2015 Nethersoft (Sebastian Kenter). All rights reserved.

#pragma once

#include "Object.h"
#include "PhotonImports.h"
#include "PhotonEngineListener.h"
#include "PhotonEngineForwarder.h"
#include "PhotonEngineClient.generated.h"

/**
 * 
 */
UCLASS()
class WORLDOFELEMENTS_API UPhotonEngineClient : public UObject
{
	GENERATED_BODY()
	
public:

    UPhotonEngineClient(const FObjectInitializer& ObjectInitializer);
	
    virtual void PostInitProperties() override;

    void PhotonCallService(bool bDispatchIncomingCommands);
    void PhotonSendOperationRequest(int32 FoperationCode, TArray<FPhotonOperationRequestParameters> FoperationParameters, int32 FChannelId);
    void PhotonSetConnectionState(bool bIsConnecting, bool bIsConnected);
    bool PhotonGetIsConnecting();
    bool PhotonGetIsConnected();

    UPhotonEngineForwarder* GetPhotonForwarder();
    void SetActivePhotonForwarder(UPhotonEngineForwarder* FActivePhotonForwarder);

private:

    FString ServerAddress = "127.0.0.1:5055";
    FString ApplicationName = "MasterServer";

    bool bSendReliable = true;
    bool bSendEncrypted = true;
	
    PhotonPeer* FPhotonPeer;
    PhotonEngineListener* FPhotonEngineListener;

    UPROPERTY()
    UPhotonEngineForwarder* FPhotonEngineForwarder;

    bool bPhotonIsConnecting;
    bool bPhotonIsConnected;
};
