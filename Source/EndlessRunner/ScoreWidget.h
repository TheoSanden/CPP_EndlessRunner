// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/TextBlock.h"
#include "Components/HorizontalBox.h"
#include "Components/Image.h"
#include "Styling/SlateBrush.h"
#include "ScoreWidget.generated.h"

/**
 * 
 */
UCLASS()
class ENDLESSRUNNER_API UScoreWidget : public UUserWidget
{
	GENERATED_BODY()

	bool Initialize() override;
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UTextBlock* PlayerOne_ScoreText;
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UTextBlock* PlayerTwo_ScoreText;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UHorizontalBox* PlayerOne_HealthBarContainer;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UHorizontalBox* PlayerTwo_HealthBarContainer;

	UPROPERTY()
		TArray<UImage*> PlayerOne_HealthCounterImages;
	UPROPERTY()
		TArray<UImage*> PlayerTwo_HealthCounterImages;

	UPROPERTY(EditAnywhere)
	FSlateBrush HealthFill;
	UPROPERTY(EditAnywhere)
	FSlateBrush HealthEmpty;

public:
	void SetScoreText(int PlayerIndex,FString Text);
	void SetPlayerHealth(int PlayerIndex, int Amount);
};
