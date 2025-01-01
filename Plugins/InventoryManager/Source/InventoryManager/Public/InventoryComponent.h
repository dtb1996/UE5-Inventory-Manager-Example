// Copyright 2024, Bit Gaming Studio. All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "InventoryItemInfo.h"
#include "InventoryItemName.h"
#include "InventoryComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FInventoryUpdatedSignature, const TArray<FInventoryItemInfo>&, NewInventoryItems);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class INVENTORYMANAGER_API UInventoryComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UInventoryComponent();

	UPROPERTY(BlueprintAssignable, Category = "Inventory")
	FInventoryUpdatedSignature OnInventoryUpdatedDelegate;

protected:
	virtual void BeginPlay() override;

	UPROPERTY(BlueprintReadWrite)
	TArray<FInventoryItemInfo> InventoryItems;

public:	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintCallable)
	void AddItem(const EInventoryItemName ItemName, const int32 Quantity);

	UFUNCTION(BlueprintCallable)
	void RemoveItem(const EInventoryItemName ItemName, const bool RemoveAll, const int32 QuantityToRemove, bool& Success);

	UFUNCTION(BlueprintCallable)
	void ClearInventory();

	UFUNCTION(BlueprintCallable, BlueprintPure)
	const bool HasItem(const EInventoryItemName ItemName, int32& Quantity) const;

	UFUNCTION(BlueprintCallable, BlueprintPure)
	const TArray<FInventoryItemInfo> GetInventoryItems() const;
};
