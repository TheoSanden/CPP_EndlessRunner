// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ObstacleSpawner.h"
#include "MovingObjectSpawner.generated.h"

USTRUCT(BlueprintType)
struct FWeightedMovingObjects
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Variables")
	TSubclassOf<AMovingDirectionalObject> Object;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Variables")
	int Weight;
};


UCLASS()
class ENDLESSRUNNER_API AMovingObjectSpawner : public AObstacleSpawner
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMovingObjectSpawner();
protected:

	UPROPERTY(EditAnywhere)
	TArray<FWeightedMovingObjects> WeightedObjectsArray;

	TMap<TSubclassOf<AMovingDirectionalObject>, ActorPooler<AMovingDirectionalObject>*> PoolMap;

	UPROPERTY(EditAnywhere)
	float SpawnWidth;
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	void Initialize();
	virtual void CheckSpawn(float DeltaTime) override; 
	virtual void Spawn(FVector Position) override;
	virtual void EnqueueObject(TObjectPtr<AMovingDirectionalObject> obj) override;
	TSubclassOf<AMovingDirectionalObject> GetClassToSpawn();
#pragma region Weights
	void CalculateWeights();
	int LastIndexWeightReference;
	TArray<int> CompoundedWeights;
#pragma endregion
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	

};
