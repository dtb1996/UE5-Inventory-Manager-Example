// Copyright 2025, Bit Gaming Studio. All Rights Reserved

#include "ItemBase.h"
#include "InventoryInterface.h"
#include "InventoryFunctionLibrary.h"
#include "Kismet/GameplayStatics.h"

AItemBase::AItemBase()
{
	PrimaryActorTick.bCanEverTick = false;

	DefaultSceneRoot = CreateDefaultSubobject<USceneComponent>(FName("DefaultSceneRoot"));
	SetRootComponent(DefaultSceneRoot);

	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(FName("StaticMesh"));
	StaticMesh->SetupAttachment(DefaultSceneRoot);

	BoxCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxCollision"));
	BoxCollision->SetBoxExtent(FVector(50.0f, 50.0f, 50.0f));
	BoxCollision->SetupAttachment(DefaultSceneRoot);

	if (ItemName == EInventoryItemName::None)
	{
		UE_LOG(LogTemp, Warning, TEXT("ItemBase: ItemName is \'None\'"));
		if (GEngine)
			GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, FString::Printf(TEXT("ItemBase: ItemName is \'None\'")));
		return;
	}
	
	bool ItemInfoFound = false;
	ItemInfo = UInventoryFunctionLibrary::GetInventoryItemInfo(ItemName, ItemInfoFound);
	ItemInfo.CurrentStack = 1;

	if (!ItemInfoFound)
	{
		UE_LOG(LogTemp, Warning, TEXT("ItemBase: ItemInfo not found"));
		if (GEngine)
			GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, FString::Printf(TEXT("ItemBase: ItemInfo not found")));
		return;
	}
}

void AItemBase::BeginPlay()
{
	Super::BeginPlay();

	BoxCollision->OnComponentBeginOverlap.AddDynamic(this, &AItemBase::OverlapBegin);
}

void AItemBase::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);

	BoxCollision->OnComponentBeginOverlap.RemoveDynamic(this, &AItemBase::OverlapBegin);
}

void AItemBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AItemBase::OverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor != UGameplayStatics::GetPlayerPawn(GetWorld(), 0))
	{
		return;
	}

	if (!IsInteractable)
	{
		return;
	}

	/*bool ItemInfoFound = false;
	FInventoryItemInfo ItemInfo = UInventoryFunctionLibrary::GetInventoryItemInfo(ItemName, ItemInfoFound);*/

	/*if (!ItemInfoFound)
	{
		UE_LOG(LogTemp, Warning, TEXT("CollectibleItemBase: ItemInfo not found"));
		if (GEngine)
			GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, FString::Printf(TEXT("CollectibleItemBase: ItemInfo not found")));

		return;
	}*/

	bool Success = false;

	APlayerController* PC = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	if (PC->GetClass()->ImplementsInterface(UInventoryInterface::StaticClass()))
	{
		Success = IInventoryInterface::Execute_PickupItem(PC, ItemInfo);
	}

	if (PickupSound)
	{
		UGameplayStatics::PlaySound2D(GetWorld(), PickupSound, 1.0f, 1.0f, 0.0f, NULL, nullptr, false);
	}

	if (DestroyOnCollected)
	{
		Destroy();
	}

	return;
}
