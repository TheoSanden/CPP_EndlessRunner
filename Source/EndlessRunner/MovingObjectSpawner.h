// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ObstacleSpawner.h"
#include "MovingObjectSpawner.generated.h"

UCLASS()
class ENDLESSRUNNER_API AMovingObjectSpawner : public AObstacleSpawner
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMovingObjectSpawner();
protected:
	UPROPERTY(EditAnywhere)
	float SpawnWidth;
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void CheckSpawn(float DeltaTime) override; 
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	

};
