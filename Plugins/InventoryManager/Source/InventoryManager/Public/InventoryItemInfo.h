// Copyright 2025, Bit Gaming Studio. All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "InventoryItemType.h"
#include "InventoryItemName.h"
#include "InventoryItemInfo.generated.h"

USTRUCT(BlueprintType)
struct FInventoryItemInfo : public FTableRowBase
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    EInventoryItemName ItemName;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    UTexture2D* ItemImage;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TSoftObjectPtr<UStaticMesh> ItemModel;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int32 CurrentStack;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int32 MaxStack;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int32 ItemIndex;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    EInventoryItemType ItemType;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int32 Price;
};

