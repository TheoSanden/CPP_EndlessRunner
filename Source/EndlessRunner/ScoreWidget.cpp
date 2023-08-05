// Fill out your copyright notice in the Description page of Project Settings.


#include "ScoreWidget.h"

void UScoreWidget::SetScoreText(int PlayerIndex,FString Text)
{
	switch(PlayerIndex)
	{
	case 0:
		PlayerOne_ScoreText->SetText(FText::FromString(Text));
		break;
	case 1:
		PlayerTwo_ScoreText->SetText(FText::FromString(Text));
	default:
		UE_LOG(LogTemp, Warning, TEXT("Widget Bindings For this Index Is not Set Up"));
	}
}

bool UScoreWidget::Initialize()
{
	bool Success = Super::Initialize();

	if(Success)
	{
		if(!PlayerOne_ScoreText || !PlayerTwo_ScoreText)
		{
			UE_LOG(LogTemp,Warning, TEXT("Score Text Blocks Not Found!"))
		}
		if(PlayerOne_HealthBarContainer && PlayerTwo_HealthBarContainer)
		{
			auto ImageArrayOne = PlayerOne_HealthBarContainer->GetAllChildren();

			for(UWidget* Widget : ImageArrayOne)
			{
				if(UImage* Image = CastChecked<UImage>(Widget))
				{
					PlayerOne_HealthCounterImages.Add(Image);
				}
			}

			auto ImageArrayTwo = PlayerTwo_HealthBarContainer->GetAllChildren();

			for (UWidget* Widget : ImageArrayTwo)
			{
				if (UImage* Image = CastChecked<UImage>(Widget))
				{
					PlayerTwo_HealthCounterImages.Add(Image);
				}
			}
		}
	}

	return Success;
}

void UScoreWidget::SetPlayerHealth(int PlayerIndex, int Amount)
{
	switch (PlayerIndex)
	{
	case 0:
		for(int i = 0; i < PlayerOne_HealthCounterImages.Num(); i++)
		{
			if(i < Amount)
			{
				PlayerOne_HealthCounterImages[i]->Brush = HealthFill;
			}
			else
			{
				PlayerOne_HealthCounterImages[i]->Brush = HealthEmpty;
			}
		}
		break;
	case 1:
		for (int i = 0; i < PlayerTwo_HealthCounterImages.Num(); i++)
		{
			if (i < Amount)
			{
				PlayerTwo_HealthCounterImages[i]->Brush = HealthFill;
			}
			else
			{
				PlayerTwo_HealthCounterImages[i]->Brush = HealthEmpty;
			}
		}
		break;
	}
}