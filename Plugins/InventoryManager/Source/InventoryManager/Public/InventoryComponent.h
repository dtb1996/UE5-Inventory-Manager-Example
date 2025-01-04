// Copyright 2025, Bit Gaming Studio. All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "InventoryItemInfo.h"
#include "InventoryItemName.h"
#include "InventoryComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FInventoryUpdatedSignature, const TArray<FInventoryItemInfo>&, NewInventoryItems);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FItemAddedSignature, const FInventoryItemInfo&, NewInventoryItem);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class INVENTORYMANAGER_API UInventoryComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UInventoryComponent();

	UPROPERTY(BlueprintAssignable, Category = "Inventory Manager")
	FInventoryUpdatedSignature OnInventoryUpdatedDelegate;

	UPROPERTY(BlueprintAssignable, Category = "Inventory Manager")
	FItemAddedSignature OnItemAddedDelegate;

protected:
	virtual void BeginPlay() override;

	TArray<FInventoryItemInfo> InventoryItems;

public:	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	/**
	* Adds an item to the inventory
	*/
	UFUNCTION(BlueprintCallable, Category = "Inventory Manager")
	void AddItem(const EInventoryItemName ItemName, const int32 Quantity);

	/**
	* Removes an item from the inventory
	*/
	UFUNCTION(BlueprintCallable, Category = "Inventory Manager")
	void RemoveItem(const EInventoryItemName ItemName, const bool RemoveAll, const int32 QuantityToRemove, bool& Success);

	/**
	* Removes all items from the inventory
	*/
	UFUNCTION(BlueprintCallable, Category = "Inventory Manager")
	void ClearInventory();

	/**
	* Checks if the item is present in the inventory
	*/
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Inventory Manager")
	const bool HasItem(const EInventoryItemName ItemName, int32& Quantity) const;

	/**
	* Returns an array of all items in the inventory
	*/
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Inventory Manager")
	const TArray<FInventoryItemInfo> GetItems() const;

	/**
	* Sorts items in the inventory by item type
	*/
	UFUNCTION(BlueprintCallable, Category = "Inventory Manager")
	void SortItemsByType();
};
