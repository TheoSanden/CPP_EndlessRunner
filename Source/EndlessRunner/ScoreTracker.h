// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ScoreWidget.h"
#include "HighScoreWidget.h"
#include "HighscoreSaveGame.h"
#include "GameFramework/Actor.h"
#include "ScoreTracker.generated.h"

UCLASS()
class ENDLESSRUNNER_API AScoreTracker : public AActor
{
	GENERATED_BODY()

	const FString HighscoreSaveSlot = "HighscoreSaveSlot";
public:	
	// Sets default values for this actor's properties
	AScoreTracker();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere)
	TSubclassOf<UScoreWidget> ScoreWidgetClass;

	UPROPERTY(BlueprintReadWrite)
	UScoreWidget* ScoreWidget;

	UPROPERTY(EditAnywhere)
	TSubclassOf<UHighScoreWidget> HighScoreWidgetClass;

	UPROPERTY(BlueprintReadWrite)
	UHighScoreWidget* HighScoreWidget;

	float TestTimer = 0;

	float PlayerOneScore;
	float PlayerTwoScore;

	bool PlayerOneActive = true;
	bool PlayerTwoActive = true;

	UPROPERTY()
	UHighscoreSaveGame* SaveGame;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	void UpdatePlayerHealth(int PlayerIndex, int NewHealth);
	void ChangePlayerScore(int PlayerIndex, int Amount);
	void TogglePlayerScore(int PlayerIndex, bool State);
	//returns the indicies of the highscore
	TArray<int> SaveScoresToFile();
	void DisplayHighScoreWidget(bool Show);
};
