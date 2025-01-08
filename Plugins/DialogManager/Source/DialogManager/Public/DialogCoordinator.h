// Copyright 2025, Bit Gaming Studio. All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "DialogCoordinator.generated.h"

UCLASS()
class DIALOGMANAGER_API UDialogCoordinator : public UObject
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = "Dialog Manager")
	void StartDialog(int32 DialogId);

	UFUNCTION(BlueprintCallable, Category = "Dialog Manager")
	void HandlePlayerResponse(int32 ResponseIndex);

private:
	void DisplayNextLine();

};
