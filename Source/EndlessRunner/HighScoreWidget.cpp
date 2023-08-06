// Fill out your copyright notice in the Description page of Project Settings.


#include "HighScoreWidget.h"


bool UHighScoreWidget::Initialize()
{
	bool Success = Super::Initialize();

	if (Success)
	{
		if (!HighScore)
		{
			UE_LOG(LogTemp, Warning, TEXT("Highscore Container not found!"))
			return false;
		}
		auto TextArrayTemp = HighScore->GetAllChildren();

		for (UWidget* Widget : TextArrayTemp)
		{
			if (UTextBlock* TextBlock = CastChecked<UTextBlock>(Widget))
			{
				TextArray.Add(TextBlock);
			}
		}
	}
	return Success;
}

void UHighScoreWidget::UpdateHighScore(TArray<FSaveValues> HighscoreArray)
{
	for(int i = 0; i < TextArray.Num(); i++)
	{
		if(i < HighscoreArray.Num())
		{
			FString a = HighscoreArray[i].name;
			FString b = FString(": ");
			FString c = FString::FromInt(HighscoreArray[i].score);
			FText text = FText::FromString(a + b + c);
			TextArray[i]->SetText(text);
		}
		else
		{
			TextArray[i]->SetText(FText::FromString(""));
		}
	}
}
