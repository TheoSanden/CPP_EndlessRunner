// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ObstacleSpawner.h"
#include "PlatformSpawner.generated.h"

UCLASS()
class ENDLESSRUNNER_API APlatformSpawner : public AObstacleSpawner
{
	GENERATED_BODY()
private: 
	TObjectPtr<AMovingDirectionalObject> PlatformReference;
protected: 
	float PlatformSize = 0;
public:	
	// Sets default values for this actor's properties
	APlatformSpawner();
private:
	virtual void CreatePlatformReference();
	virtual void CalculatePlatformMetrics();
	virtual void InstantiateInitialPlatform();
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;


};
