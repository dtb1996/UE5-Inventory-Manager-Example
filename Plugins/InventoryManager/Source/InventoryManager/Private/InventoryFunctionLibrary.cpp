// Copyright 2025, Bit Gaming Studio. All Rights Reserved

#include "InventoryFunctionLibrary.h"

#define DATA_TABLE_PATH "/InventoryManager/Example/DT_ItemInfo.DT_ItemInfo"

FInventoryItemInfo UInventoryFunctionLibrary::GetInventoryItemInfo(EInventoryItemName ItemName, bool& ItemFound)
{
	FInventoryItemInfo ItemInfo;
	ItemFound = false;

	UDataTable* DT;
	FSoftObjectPath DTPath = FSoftObjectPath(TEXT(DATA_TABLE_PATH));

	DT = Cast<UDataTable>(DTPath.ResolveObject());

	if (!DT)
	{
		UE_LOG(LogTemp, Warning, TEXT("InventoryFunctionLibrary: DTPath not resolved, trying to load..."));

		DT = Cast<UDataTable>(DTPath.TryLoad());
	}

	FDataTableRowHandle ItemInfoRow;

	ItemInfoRow.DataTable = DT;

	FString RowNameStr = UEnum::GetValueAsString(ItemName);
	ItemInfoRow.RowName = FName(RowNameStr.RightChop(RowNameStr.Find("::") + 2));

	const auto ItemData = ItemInfoRow.GetRow<FInventoryItemInfo>("");
	if (ItemData)
	{
		ItemFound = true;
		ItemInfo = *ItemData;
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("InventoryFunctionLibrary: ItemData not found"));
	}

	return ItemInfo;
}
