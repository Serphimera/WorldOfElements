// Copyright 2015 Nethersoft (Sebastian Kenter). All rights reserved.

#pragma once

#include "PhotonEngineDefinitions.generated.h"

USTRUCT(BlueprintType)
struct FPhotonOperationRequestParameters
{
    GENERATED_USTRUCT_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = PhotonRequestData)
    uint8 FPhotonOperationRequestParameterCode;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = PhotonRequestData)
    FString FPhotonOperationRequestParameterString;

    FPhotonOperationRequestParameters()
    {
        FPhotonOperationRequestParameterCode = 0;
        FPhotonOperationRequestParameterString = "";
    }
};

USTRUCT(BlueprintType)
struct FPhotonOperationResponseParameters
{
    GENERATED_USTRUCT_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = PhotonResponseData)
    uint8 FPhotonOperationResponseParameterCode;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = PhotonResponseData)
    FString FPhotonOperationResponseParameterString;

    FPhotonOperationResponseParameters()
    {
        FPhotonOperationResponseParameterCode = 0;
        FPhotonOperationResponseParameterString = "";
    }
};

USTRUCT(BlueprintType)
struct FPhotonOperationResponse
{
    GENERATED_USTRUCT_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = PhotonResponseData)
    uint8 FPhotonOperationResponseCode;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = PhotonResponseData)
    uint8 FPhotonOperationResponseReturnCode;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = PhotonResponseData)
    FString FPhotonOperationResponseDebugMessage;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = PhotonResponseData)
    TArray<FPhotonOperationResponseParameters> FPhotonResponseParameters;

    FPhotonOperationResponse()
    {
        FPhotonOperationResponseCode = 0;
        FPhotonOperationResponseReturnCode = 0;
        FPhotonOperationResponseDebugMessage = "";
        FPhotonResponseParameters.Empty();
    }
};

USTRUCT(BlueprintType)
struct FPhotonEventData
{
    GENERATED_USTRUCT_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = PhotonEventData)
    int32 FPhotonEventCode;

    FPhotonEventData()
    {
        FPhotonEventCode = 0;
    }
};

USTRUCT(BlueprintType)
struct FPhotonDebugData
{
    GENERATED_USTRUCT_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = PhotonDebugData)
    int32 FPhotonDebugCode;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = PhotonDebugData)
    FString FPhotonDebugMessage;

    FPhotonDebugData()
    {
        FPhotonDebugCode = 0;
        FPhotonDebugMessage = "";
    }
};