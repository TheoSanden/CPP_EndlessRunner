// Fill out your copyright notice in the Description page of Project Settings.


#include "ScoreTracker.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AScoreTracker::AScoreTracker()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AScoreTracker::BeginPlay()
{
	Super::BeginPlay();
	if (ScoreWidgetClass != nullptr)
	{
		ScoreWidget = CreateWidget<UScoreWidget>(GetWorld(), ScoreWidgetClass);
		ScoreWidget->AddToViewport(9999);
	}

	if (HighScoreWidgetClass != nullptr)
	{
		HighScoreWidget = CreateWidget<UHighScoreWidget>(GetWorld(), HighScoreWidgetClass);
		HighScoreWidget->AddToViewport(9999);
	    HighScoreWidget->SetVisibility(ESlateVisibility::Hidden);
	}
	bool HighScoreExists = UGameplayStatics::DoesSaveGameExist(HighscoreSaveSlot, 0);

	if (HighScoreExists)
	{
		SaveGame = Cast<UHighscoreSaveGame>(UGameplayStatics::LoadGameFromSlot(HighscoreSaveSlot, 0));
	}
	else
	{
		SaveGame = Cast<UHighscoreSaveGame>(UGameplayStatics::CreateSaveGameObject(UHighscoreSaveGame::StaticClass()));
	}
}
void AScoreTracker::TogglePlayerScore(int PlayerIndex, bool State)
{
	switch (PlayerIndex)
	{
	case 0:
		PlayerOneActive = State;
	case 1:
		PlayerTwoActive = State;
	default:
		break;
	}
}
// Called every frame
void AScoreTracker::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if(PlayerOneActive)
	{
		PlayerOneScore += DeltaTime;
		ScoreWidget->SetScoreText(0, FString::FromInt((int)PlayerOneScore));
	}

	if(PlayerTwoActive)
	{
		PlayerTwoScore += DeltaTime;
		ScoreWidget->SetScoreText(1, FString::FromInt((int)PlayerTwoScore));
	}
}

void AScoreTracker::UpdatePlayerHealth(int PlayerIndex, int NewHealth)
{
	if(PlayerIndex > 1)
	{
		return;
	}
	ScoreWidget->SetPlayerHealth(PlayerIndex,NewHealth);
}

void AScoreTracker::ChangePlayerScore(int PlayerIndex, int Amount)
{
	switch(PlayerIndex)
	{
	case 0:
		if((PlayerOneScore + (float)Amount) < 0)
		{
			PlayerOneScore = 0;
		}
		else
		{
			PlayerOneScore += Amount;
		}
		ScoreWidget->SetScoreText(PlayerIndex, FString::FromInt((int)PlayerOneScore));
		break;
	case 1:
		if ((PlayerTwoScore + (float)Amount) < 0)
		{
			PlayerTwoScore = 0;
		}
		else
		{
			PlayerTwoScore += Amount;
		}
		ScoreWidget->SetScoreText(PlayerIndex, FString::FromInt((int)PlayerTwoScore));
		break;
	default: return;
	}
}

TArray<int> AScoreTracker::SaveScoresToFile()
{
	FString P1Name = FString("Player One");
	FString P2Name = FString("Player Two");
	FSaveValues PlayerOneScoreValues(P1Name, PlayerOneScore);
	FSaveValues PlayerTwoScoreValues(P2Name, PlayerTwoScore);
	TArray<int> ScoreIndicies = SaveGame->TryInsertScore(PlayerOneScoreValues, PlayerTwoScoreValues);
	UGameplayStatics::SaveGameToSlot(SaveGame, HighscoreSaveSlot, 0);
	return ScoreIndicies;
}

void AScoreTracker::DisplayHighScoreWidget(bool Show)
{
	if(Show)
	{
		HighScoreWidget->UpdateHighScore(SaveGame->Scores);
		HighScoreWidget->SetVisibility(ESlateVisibility::Visible);
		ScoreWidget->SetVisibility(ESlateVisibility::Hidden);
	}
}
