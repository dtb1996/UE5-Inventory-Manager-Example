// Copyright 2024, Bit Gaming Studio. All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "InventoryItemInfo.h"
#include "InventoryItemName.h"
#include "InventoryFunctionLibrary.generated.h"

UCLASS()
class INVENTORYSYSTEM_API UInventoryFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintPure, BlueprintCallable, Category = "Inventory Manager")
	static FInventoryItemInfo GetInventoryItemInfo(EInventoryItemName ItemName, bool& ItemFound);	
};
