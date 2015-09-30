// Copyright 2015 Nethersoft (Sebastian Kenter). All rights reserved.

#include "WorldOfElements.h"
#include "WoEGameInstance.h"
#include "WoELoginPlayerController.h"

void AWoELoginPlayerController::BeginPlay()
{
    UWoEGameInstance* ThisGameInstance = CastChecked<UWoEGameInstance>(GetWorld()->GetGameInstance());

    ThisGameInstance->GetPhotonForwarder()->ForwardPhotonOperationResponse.AddDynamic(this, &AWoELoginPlayerController::HandleOperationResponse);
    ThisGameInstance->GetPhotonForwarder()->ForwardPhotonEvent.AddDynamic(this, &AWoELoginPlayerController::HandleEvent);
    ThisGameInstance->GetPhotonForwarder()->ForwardPhotonStatusChange.AddDynamic(this, &AWoELoginPlayerController::HandleStatusChanged);
    ThisGameInstance->GetPhotonForwarder()->ForwardPhotonDebugReturn.AddDynamic(this, &AWoELoginPlayerController::HandleDebugReturn);

    Super::BeginPlay();
}