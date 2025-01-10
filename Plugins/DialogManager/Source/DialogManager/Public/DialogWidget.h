// Copyright 2025, Bit Gaming Studio. All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "DialogEntry.h"
#include "DialogWidget.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FConversationCompletedSignature);

UCLASS(Abstract)
class DIALOGMANAGER_API UDialogWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintAssignable, Category = "Dialog Manager")
	FConversationCompletedSignature OnConversationCompletedDelegate;

	UPROPERTY(BlueprintReadWrite, meta = (ExposeOnSpawn = true))
	int32 FirstLineId;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UDataTable* DialogDataTable;
	
protected:
	virtual void NativeConstruct() override;

	UFUNCTION(BlueprintCallable)
	void GetNextLine(int32 LineId);

	UFUNCTION(BlueprintCallable)
	void OnAdvanceButtonClicked();

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UTextBlock* DialogText;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UTextBlock* SpeakerNameText;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UImage* SpeakerPortrait;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UButton* AdvanceTextButton;

	UPROPERTY(BlueprintReadWrite)
	int32 NextLineId;
};
