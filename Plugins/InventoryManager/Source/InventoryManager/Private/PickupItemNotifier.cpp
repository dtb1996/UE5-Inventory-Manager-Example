// Copyright 2025, Bit Gaming Studio. All Rights Reserved

#include "PickupItemNotifier.h"
#include "Components/TextBlock.h"

void UPickupItemNotifier::NativePreConstruct()
{
	Super::NativePreConstruct();

	int32 Quantity = ItemInfo.CurrentStack;

	FText ItemName = FText::Format(UEnum::GetDisplayValueAsText(ItemInfo.ItemName), FText::FromString(FString(Quantity > 1 ? "s" : "")));
	
	FText QuantityObtained = FText::FromString(FString("Obtained ") + FString::FromInt(Quantity));

	ItemNameText->SetText(ItemName);

	QuantityText->SetText(QuantityObtained);
}

void UPickupItemNotifier::NativeConstruct()
{
	Super::NativeConstruct();

	PlayFadeInAnim();
}
