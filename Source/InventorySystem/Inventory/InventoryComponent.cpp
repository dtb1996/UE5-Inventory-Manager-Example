// Copyright 2024, Bit Gaming Studio. All Rights Reserved


#include "InventoryComponent.h"

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
	if (InventoryMap.Contains(ItemName))
	{
		InventoryMap.SetQuantity(ItemName, InventoryMap.Find(ItemName) + Quantity); //TODO: check max quantity
		//InventoryMap.Map[ItemName]
	}
	else
	{
		InventoryMap.Add(ItemName, Quantity);
	}

	OnInventoryUpdatedDelegate.Broadcast(InventoryMap);
}

//void UInventoryComponent::AddItem(FInventoryItemInfo ItemInfo)
//{
//	int32 ItemIndex = 0;
//	FInventoryItemInfo FoundItem;
//	bool ItemFound = false;
//
//	for (int i = 0; i < InventoryItems.Num(); i++)
//	{
//		if ((ItemInfo.ItemName == InventoryItems[i].ItemName) && (InventoryItems[i].CurrentStack < ItemInfo.MaxStack))
//		{
//			ItemIndex = i;
//			FoundItem = InventoryItems[i];
//			ItemFound = true;
//			break;
//		}
//	}
//
//	if (ItemFound)
//	{
//		FoundItem.CurrentStack = FoundItem.CurrentStack + ItemInfo.CurrentStack > FoundItem.MaxStack ? FoundItem.MaxStack : FoundItem.CurrentStack + ItemInfo.CurrentStack;
//		InventoryItems[ItemIndex] = FoundItem;
//	}
//	else
//	{
//		ItemIndex = InventoryItems.Add(ItemInfo);
//		InventoryItems[ItemIndex].ItemIndex = ItemIndex;
//	}
//
//	OnInventoryUpdatedDelegate.Broadcast(InventoryItems);
//}

void UInventoryComponent::RemoveItem(const EInventoryItemName ItemName, const bool RemoveAll, const int32 QuantityToRemove, bool& Success)
{
	if (!InventoryMap.Contains(ItemName))
	{
		Success = false;
		return;
	}

	if (RemoveAll)
	{
		InventoryMap.Remove(ItemName);
	}
	else
	{
		int32 NewQuantity = FMath::Clamp(InventoryMap.Find(ItemName) - QuantityToRemove, 0, 99); //TODO: get max quantity
		if (NewQuantity <= 0)
		{
			InventoryMap.Remove(ItemName);
		}
		else
		{
			InventoryMap.SetQuantity(ItemName, NewQuantity);
		}
	}

	OnInventoryUpdatedDelegate.Broadcast(InventoryMap);

	Success = true;
}

//void UInventoryComponent::RemoveItem(EInventoryItemName ItemName, bool RemoveAll, int32 QuantityToRemove, bool& Success)
//{
//	for (int i = 0; i < InventoryItems.Num(); i++)
//	{
//		FInventoryItemInfo CurrentItem = InventoryItems[i];
//		if (ItemName != CurrentItem.ItemName)
//		{
//			continue;
//		}
//
//		if (!RemoveAll && !((FMath::Clamp(CurrentItem.CurrentStack - QuantityToRemove, 0, CurrentItem.MaxStack)) > 0))
//		{
//			CurrentItem.CurrentStack = FMath::Clamp(CurrentItem.CurrentStack - QuantityToRemove, 0, CurrentItem.MaxStack);
//			if (CurrentItem.CurrentStack <= 0)
//			{
//				InventoryItems.RemoveAt(i);
//			}
//			else
//			{
//				InventoryItems[i] = CurrentItem;
//			}
//		}
//		else
//		{
//			InventoryItems.RemoveAt(i, EAllowShrinking::Yes);
//		}
//
//		OnInventoryUpdatedDelegate.Broadcast(InventoryItems);
//
//		Success = true;
//		break;
//	}
//}

void UInventoryComponent::ClearInventory()
{
	InventoryMap.Empty();
	OnInventoryUpdatedDelegate.Broadcast(InventoryMap);
}

const bool UInventoryComponent::HasItem(const EInventoryItemName ItemName, int32& Quantity) const
{
	Quantity = 0;

	if (InventoryMap.Contains(ItemName))
	{
		Quantity = InventoryMap.Find(ItemName);
	}

	return Quantity > 0;

	/*for (const FInventoryItemInfo ItemInfo : InventoryItems)
	{
		if (ItemName == ItemInfo.ItemName)
		{
			Quantity = ItemInfo.CurrentStack;
			return Quantity > 0;
		}
	}

	return false;*/
}

const TMap<EInventoryItemName, int32> UInventoryComponent::GetInventoryItems() const
{
	return InventoryMap.GetItems();
	//return TMap<EInventoryItemName, int32>();
}

