// Copyright 2025, Bit Gaming Studio. All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "InventoryItemInfo.h"
#include "PickupItemNotifier.generated.h"

UCLASS(Abstract)
class INVENTORYMANAGER_API UPickupItemNotifier : public UUserWidget
{
	GENERATED_BODY()
	
protected:
	virtual void NativePreConstruct() override;

	virtual void NativeConstruct() override;

	UFUNCTION(BlueprintImplementableEvent)
	void PlayFadeInAnim();

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void PlayFadeOutAnim();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ExposeOnSpawn = true))
	FInventoryItemInfo ItemInfo;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UTextBlock* ItemNameText;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UTextBlock* QuantityText;
};
