// Copyright 2015 Nethersoft (Sebastian Kenter). All rights reserved.

#include "WorldOfElements.h"
#include "WoELoginGameMode.h"

AWoELoginGameMode::AWoELoginGameMode(const FObjectInitializer& ObjectInitializer)
    : Super(ObjectInitializer)
{
    PlayerControllerClass = AWoELoginPlayerController::StaticClass();
}


