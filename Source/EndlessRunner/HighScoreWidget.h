// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/VerticalBox.h"
#include "Components/TextBlock.h"
#include "Blueprint/UserWidget.h"
#include "HighscoreSaveGame.h"
#include "HighScoreWidget.generated.h"

/**
 * 
 */
UCLASS()
class ENDLESSRUNNER_API UHighScoreWidget : public UUserWidget
{
	GENERATED_BODY()

		bool Initialize() override;
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UVerticalBox* HighScore;
	UPROPERTY()
	TArray<UTextBlock*> TextArray;
public:
	void UpdateHighScore(TArray<FSaveValues> HighscoreArray);
};
