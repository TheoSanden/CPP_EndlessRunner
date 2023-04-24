// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MovingDirectionalObject.h"
#include "ActorPooler.h"
#include "ObstacleSpawner.generated.h"

UCLASS()
class ENDLESSRUNNER_API AObstacleSpawner : public AActor
{
	GENERATED_BODY()

protected:
	float SpawnTimer;

public:	
	// Sets default values for this actor's properties
	AObstacleSpawner();
	~AObstacleSpawner();
protected:
#pragma region Editable Variables 
	UPROPERTY(EditDefaultsOnly, Category = Obstacle)
	TSubclassOf<AMovingDirectionalObject> ObstacleToSpawn;

	UPROPERTY(EditAnywhere, Category = Obstacle)
	FVector ObstacleTravelDirection = FVector(0,1,0);
	UPROPERTY(EditAnywhere, Category = Obstacle)
	float DeafultObjectSpeed = 0.0f;
	UPROPERTY(EditAnywhere, Category = Spawn)
	bool bTileSpawn;
	UPROPERTY(EditAnyWhere, Category = Spawn)
	float SpawnRateInSeconds = 2.0f;
#pragma endregion
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	//TArray<TObjectPtr<AMovingDirectionalObject>> ActiveObstacles;
	ActorPooler<AMovingDirectionalObject>* ObstaclePooler = nullptr;
	TArray<TObjectPtr<AMovingDirectionalObject>> ActiveObjects;
	UPROPERTY(EditAnywhere, Category = Obstacle)
	float KillDistance;
	virtual void Spawn(FVector Position);
	virtual void CheckSpawn(float DeltaTime);
	virtual void CheckObstacleReachEnd();
	virtual void UpdateObjectSpeed(float MovementSpeed);
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
