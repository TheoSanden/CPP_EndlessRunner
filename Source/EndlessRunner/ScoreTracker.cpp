// Fill out your copyright notice in the Description page of Project Settings.


#include "ScoreTracker.h"

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
}

// Called every frame
void AScoreTracker::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	PlayerOneScore += DeltaTime;
	PlayerTwoScore += DeltaTime;

	ScoreWidget->SetScoreText(0, FString::FromInt((int)PlayerOneScore));
	ScoreWidget->SetScoreText(1, FString::FromInt((int)PlayerTwoScore));
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

