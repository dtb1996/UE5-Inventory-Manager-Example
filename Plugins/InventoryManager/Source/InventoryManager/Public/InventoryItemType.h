// Copyright 2025, Bit Gaming Studio. All Rights Reserved

#pragma once

#include "CoreMinimal.h"

UENUM(BlueprintType)
enum class EInventoryItemType : uint8
{
	None,
	Weapons,
	Consumables,
	Armor,
	Crafting,
	Special,
	Count UMETA(Hidden)
};
ENUM_RANGE_BY_COUNT(EInventoryItemType, EInventoryItemType::Count);
