// Copyright 2025, Bit Gaming Studio. All Rights Reserved

#include "DialogWidget.h"
#include "Components/TextBlock.h"
#include "Components/Button.h"

void UDialogWidget::NativeConstruct()
{
	Super::NativeConstruct();

	if (AdvanceTextButton)
	{
		AdvanceTextButton->OnClicked.AddDynamic(this, &UDialogWidget::OnAdvanceButtonClicked);
	}

	GetNextLine(FirstLineId);
}

void UDialogWidget::GetNextLine(int32 LineId)
{
	FString str = FString("000") + FString::FromInt(000 + LineId);
	FName LineIdName = *str.Right(3);
	FDialogEntry* DialogLine = DialogDataTable->FindRow<FDialogEntry>(LineIdName, "");

	if (DialogLine)
	{
		NextLineId = DialogLine->NextLineId;

		SpeakerNameText->SetText(DialogLine->SpearkerName);
		DialogText->SetText(DialogLine->DialogText);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Dialog Manager: DataTable row not found"));
	}
}

void UDialogWidget::OnAdvanceButtonClicked()
{
	if (NextLineId == -1)
	{
		OnConversationCompletedDelegate.Broadcast();
	}

	GetNextLine(NextLineId);
}
