// Copyright 2025, Bit Gaming Studio. All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "InventoryItemName.h"
#include "InventoryItemInfo.h"
#include "Components/BoxComponent.h"
#include "PickupItem.generated.h"

UCLASS()
class INVENTORYMANAGER_API APickupItem : public AActor
{
	GENERATED_BODY()
	
public:
	APickupItem();

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (ExposeOnSpawn = true))
	EInventoryItemName ItemName;

	UPROPERTY(EditInstanceOnly, BlueprintReadOnly)
	bool bIsInteractable = true;

protected:
	virtual void BeginPlay() override;

	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

	void SetItemMesh();

	UPROPERTY()
	USceneComponent* DefaultSceneRoot;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	UStaticMeshComponent* StaticMesh;

	UBoxComponent* BoxCollision;

	UPROPERTY(EditInstanceOnly, BlueprintReadOnly)
	USoundBase* PickupSound;

	UPROPERTY(EditInstanceOnly, BlueprintReadOnly)
	bool bDestroyOnCollected = true;

	FInventoryItemInfo ItemInfo;

public:	
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	void OverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
};
