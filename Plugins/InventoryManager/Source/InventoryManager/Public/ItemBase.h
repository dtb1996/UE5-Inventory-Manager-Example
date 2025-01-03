// Copyright 2025, Bit Gaming Studio. All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "InventoryItemName.h"
#include "InventoryItemInfo.h"
#include "Components/BoxComponent.h"
#include "ItemBase.generated.h"

UCLASS(Abstract)
class INVENTORYMANAGER_API AItemBase : public AActor
{
	GENERATED_BODY()

public:
	AItemBase();

	UPROPERTY(EditInstanceOnly, BlueprintReadWrite)
	EInventoryItemName ItemName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool IsInteractable = true;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool DestroyOnCollected = true;

protected:
	virtual void BeginPlay() override;

	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

	UPROPERTY()
	USceneComponent* DefaultSceneRoot;

	UPROPERTY(EditInstanceOnly, BlueprintReadOnly)
	UStaticMeshComponent* StaticMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UBoxComponent* BoxCollision;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	USoundBase* PickupSound;

	UPROPERTY(BlueprintReadWrite)
	FInventoryItemInfo ItemInfo = FInventoryItemInfo();

public:
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	void OverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

};