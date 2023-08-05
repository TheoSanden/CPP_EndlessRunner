// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ScoreWidget.h"
#include "GameFramework/Actor.h"
#include "ScoreTracker.generated.h"

UCLASS()
class ENDLESSRUNNER_API AScoreTracker : public AActor
{
	GENERATED_BODY()
	
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

	float TestTimer = 0;

	float PlayerOneScore;
	float PlayerTwoScore;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	void UpdatePlayerHealth(int PlayerIndex, int NewHealth);
	void ChangePlayerScore(int PlayerIndex, int Amount);
};
