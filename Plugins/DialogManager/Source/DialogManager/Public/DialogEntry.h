// Copyright 2025, Bit Gaming Studio. All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "DialogEntry.generated.h"

USTRUCT(BlueprintType)
struct FDialogEntry : public FTableRowBase
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FText SpearkerName;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FText DialogText;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    USoundBase* AudioClip;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int32 NextLineId;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TArray<FText> Responses;
};