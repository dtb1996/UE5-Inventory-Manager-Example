// Copyright 2025, Bit Gaming Studio. All Rights Reserved

#include "PickupItem.h"
#include "InventoryInterface.h"
#include "InventoryFunctionLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/AssetManager.h"

APickupItem::APickupItem()
{
	PrimaryActorTick.bCanEverTick = false;

	DefaultSceneRoot = CreateDefaultSubobject<USceneComponent>(FName("DefaultSceneRoot"));
	SetRootComponent(DefaultSceneRoot);

	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(FName("StaticMesh"));
	StaticMesh->SetupAttachment(DefaultSceneRoot);

	BoxCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxCollision"));
	BoxCollision->SetBoxExtent(FVector(50.0f, 50.0f, 50.0f));
	BoxCollision->SetupAttachment(DefaultSceneRoot);
}

void APickupItem::BeginPlay()
{
	Super::BeginPlay();
	
	BoxCollision->OnComponentBeginOverlap.AddDynamic(this, &APickupItem::OverlapBegin);

	bool bItemInfoFound = false;
	ItemInfo = UInventoryFunctionLibrary::GetInventoryItemInfo(ItemName, bItemInfoFound);
	ItemInfo.CurrentStack = 1;

	if (!bItemInfoFound)
	{
		UE_LOG(LogTemp, Warning, TEXT("PickupItem: ItemInfo not found"));

		return;
	}

	if (!ItemInfo.ItemModel.IsValid())
	{
		UAssetManager::GetStreamableManager().RequestAsyncLoad(ItemInfo.ItemModel.ToSoftObjectPath(), FStreamableDelegate::CreateUObject(this, &APickupItem::SetItemMesh));
	}
	else
	{
		SetItemMesh();
	}
}

void APickupItem::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);

	BoxCollision->OnComponentBeginOverlap.RemoveDynamic(this, &APickupItem::OverlapBegin);
}

void APickupItem::SetItemMesh()
{
	UStaticMesh* Mesh = Cast<UStaticMesh>(ItemInfo.ItemModel.Get());
	StaticMesh->SetStaticMesh(Mesh);
}

void APickupItem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void APickupItem::OverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor != UGameplayStatics::GetPlayerPawn(GetWorld(), 0))
	{
		return;
	}

	if (!bIsInteractable)
	{
		return;
	}

	bool bSuccess = false;

	APlayerController* PC = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	if (PC->GetClass()->ImplementsInterface(UInventoryInterface::StaticClass()))
	{
		bSuccess = IInventoryInterface::Execute_PickupItem(PC, ItemInfo);
	}

	if (!bSuccess)
	{
		return;
	}

	if (PickupSound)
	{
		UGameplayStatics::PlaySound2D(GetWorld(), PickupSound, 1.0f, 1.0f, 0.0f, NULL, nullptr, false);
	}

	if (bDestroyOnCollected)
	{
		Destroy();
	}

	return;
}
