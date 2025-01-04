// Copyright 2025, Bit Gaming Studio. All Rights Reserved

#include "InventoryComponent.h"
#include "InventoryFunctionLibrary.h"

UInventoryComponent::UInventoryComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UInventoryComponent::BeginPlay()
{
	Super::BeginPlay();	
}

void UInventoryComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void UInventoryComponent::AddItem(const EInventoryItemName ItemName, const int32 Quantity)
{
	int32 ItemIndex = 0;
	FInventoryItemInfo FoundItem;
	bool ItemFound = false;

	for (int i = 0; i < InventoryItems.Num(); i++)
	{
		if ((ItemName == InventoryItems[i].ItemName) && (InventoryItems[i].CurrentStack < InventoryItems[i].MaxStack))
		{
			ItemIndex = i;
			FoundItem = InventoryItems[i];
			ItemFound = true;
			break;
		}
	}

	if (ItemFound)
	{
		FoundItem.CurrentStack = FMath::Clamp(FoundItem.CurrentStack + Quantity, 0, FoundItem.MaxStack);
		InventoryItems[ItemIndex] = FoundItem;

		FoundItem.CurrentStack = FMath::Clamp(Quantity, 0, FoundItem.MaxStack);
		OnItemAddedDelegate.Broadcast(FoundItem);
	}
	else
	{
		bool ItemInfoFound = false;
		
		FInventoryItemInfo NewItem = UInventoryFunctionLibrary::GetInventoryItemInfo(ItemName, ItemInfoFound);
		NewItem.CurrentStack = FMath::Clamp(Quantity, 0, NewItem.MaxStack);

		ItemIndex = InventoryItems.Add(NewItem);

		InventoryItems[ItemIndex].ItemIndex = ItemIndex;

		OnItemAddedDelegate.Broadcast(NewItem);
	}

	OnInventoryUpdatedDelegate.Broadcast(InventoryItems);
}

void UInventoryComponent::RemoveItem(const EInventoryItemName ItemName, const bool RemoveAll, const int32 QuantityToRemove, bool& Success)
{
	Success = false;
	bool ItemFound = false;
	int32 FoundItemIndex = 0;
	FInventoryItemInfo FoundItem;

	for (int i = 0; i < InventoryItems.Num(); i++)
	{
		FInventoryItemInfo CurrentItem = InventoryItems[i];

		if (ItemName != CurrentItem.ItemName)
		{
			continue;
		}

		ItemFound = true;
		FoundItemIndex = i;
		FoundItem = CurrentItem;
		break;
	}

	if (!ItemFound)
	{
		return;
	}

	if (RemoveAll)
	{
		InventoryItems.RemoveAt(FoundItemIndex, EAllowShrinking::Yes);
	}
	else
	{
		FoundItem.CurrentStack = FMath::Clamp(FoundItem.CurrentStack - QuantityToRemove, 0, FoundItem.MaxStack);
		if (FoundItem.CurrentStack <= 0)
		{
			InventoryItems.RemoveAt(FoundItemIndex, EAllowShrinking::Yes);
		}
		else
		{
			InventoryItems[FoundItemIndex] = FoundItem;
		}
	}

	OnInventoryUpdatedDelegate.Broadcast(InventoryItems);

	Success = true;
}

void UInventoryComponent::ClearInventory()
{
	InventoryItems.Empty();
	OnInventoryUpdatedDelegate.Broadcast(InventoryItems);
}

const bool UInventoryComponent::HasItem(const EInventoryItemName ItemName, int32& Quantity) const
{
	Quantity = 0;

	for (const FInventoryItemInfo ItemInfo : InventoryItems)
	{
		if (ItemName == ItemInfo.ItemName)
		{
			Quantity += ItemInfo.CurrentStack;
		}
	}

	return Quantity > 0;
}

const TArray<FInventoryItemInfo> UInventoryComponent::GetItems() const
{
	return InventoryItems;
}

void UInventoryComponent::SortItemsByType()
{
	TArray<FInventoryItemInfo> SortedInventory = TArray<FInventoryItemInfo>();
	
	for (EInventoryItemType ItemType : TEnumRange<EInventoryItemType>())
	{
		for (FInventoryItemInfo Item : InventoryItems)
		{
			if (Item.ItemType == ItemType)
			{
				SortedInventory.Add(Item);
			}
		}
	}

	InventoryItems = SortedInventory;
	OnInventoryUpdatedDelegate.Broadcast(InventoryItems);
}

