// Copyright 2024, Bit Gaming Studio. All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "InventoryItemInfo.h"
#include "InventoryItemName.h"
#include "InventoryComponent.generated.h"

USTRUCT(BlueprintType)
struct FInventoryMapType
{
	GENERATED_BODY()

	TMap<EInventoryItemName, int32> Map;

	int32 Find(const EInventoryItemName ItemName) const
	{
		return *Map.Find(ItemName);
	}

	void SetQuantity(const EInventoryItemName Key, const int32 Quantity)
	{
		Map[Key] = Quantity;
	}

	bool Contains(const EInventoryItemName ItemName) const
	{
		return Map.Contains(ItemName);
	}

	int32 Add(const EInventoryItemName ItemName, const int32 Quantity)
	{
		return Map.Add(ItemName, Quantity);
	}

	int32 Remove(const EInventoryItemName ItemName)
	{
		return Map.Remove(ItemName);
	}

	void Empty()
	{
		Map.Empty();
	}

	TMap<EInventoryItemName, int32> GetItems() const
	{
		return Map;
	}
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FInventoryUpdatedSignature, const FInventoryMapType, NewInventoryItems);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class INVENTORYSYSTEM_API UInventoryComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UInventoryComponent();

	UPROPERTY(BlueprintAssignable, Category = "Inventory")
	FInventoryUpdatedSignature OnInventoryUpdatedDelegate;

protected:
	virtual void BeginPlay() override;

	UPROPERTY(BlueprintReadWrite)
	FInventoryMapType InventoryMap;

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
	const TMap<EInventoryItemName, int32> GetInventoryItems() const;
};
