// Copyright 2025, Bit Gaming Studio. All Rights Reserved

#include "DialogWidget.h"
#include "Components/TextBlock.h"
#include "Components/Button.h"
#include "Components/Image.h"
#include "DialogEntry.h"
#include "DialogCharacterInfo.h"

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
	FString SpeakerName;

	// Lookup next dialog line
	FString str = FString("000") + FString::FromInt(000 + LineId);
	FName LineIdName = *str.Right(3);
	FDialogEntry* DialogLine = DialogDataTable->FindRow<FDialogEntry>(LineIdName, "");

	if (DialogLine)
	{
		NextLineId = DialogLine->NextLineId;

		SpeakerName = UEnum::GetValueAsString(DialogLine->SpeakerName);
		SpeakerName = SpeakerName.RightChop(SpeakerName.Find("::") + 2);

		SpeakerNameText->SetText(FText::FromString(SpeakerName));
		DialogText->SetText(DialogLine->DialogText);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("DialogWidget: DialogDataTable row not found"));
	}

	// Lookup character info
	FName SpeakerRow = FName(SpeakerName);
	FDialogCharacterInfo* SpeakerInfo = CharacterInfoDataTable->FindRow<FDialogCharacterInfo>(SpeakerRow, "");

	if (SpeakerInfo)
	{
		if (SpeakerInfo->Portrait)
		{
			SpeakerPortrait->SetBrushFromTexture(SpeakerInfo->Portrait);
		}
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("DialogWidget: CharacterInfoDataTable row not found"));
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
