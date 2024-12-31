// Copyright 2024, Bit Gaming Studio. All Rights Reserved

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
};
