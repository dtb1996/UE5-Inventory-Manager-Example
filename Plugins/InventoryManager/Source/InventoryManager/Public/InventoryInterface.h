// Copyright 2025, Bit Gaming Studio. All Rights Reserved

#pragma once

#include "InventoryItemInfo.h"
#include "InventoryInterface.generated.h"

UINTERFACE(MinimalAPI, Blueprintable)
class UInventoryInterface : public UInterface
{
	GENERATED_BODY()
};

class IInventoryInterface
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Inventory Manager")
	bool PickupItem(FInventoryItemInfo ItemName);

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Inventory Manager")
	void ItemSelected(FInventoryItemInfo ItemName);
};