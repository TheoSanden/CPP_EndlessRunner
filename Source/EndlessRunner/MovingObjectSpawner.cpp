// Fill out your copyright notice in the Description page of Project Settings.


#include "MovingObjectSpawner.h"

// Sets default values
AMovingObjectSpawner::AMovingObjectSpawner()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AMovingObjectSpawner::BeginPlay()
{
	Super::BeginPlay();
	Initialize();
}

TSubclassOf<AMovingDirectionalObject> AMovingObjectSpawner::GetClassToSpawn()
{
	int RandomWeight = FMath::RandRange(0, LastIndexWeightReference);

	for(int i = 0; i < CompoundedWeights.Num()-1; i++)
	{
		if(RandomWeight >= CompoundedWeights[i] && RandomWeight < CompoundedWeights[i+1])
		{
			return WeightedObjectsArray[i].Object;
		}
	}
	return WeightedObjectsArray[WeightedObjectsArray.Num()-1].Object;
}
void AMovingObjectSpawner::CalculateWeights()
{
	int CurrentCompoundedWeight = 0;

	for(FWeightedMovingObjects WO : WeightedObjectsArray)
	{
		CompoundedWeights.Add(CurrentCompoundedWeight);
		CurrentCompoundedWeight += WO.Weight;
	}
	LastIndexWeightReference = CurrentCompoundedWeight;
}
void AMovingObjectSpawner::Initialize()
{
	for(FWeightedMovingObjects WO : WeightedObjectsArray)
	{
		ActorPooler<AMovingDirectionalObject>* NewPool = new ActorPooler<AMovingDirectionalObject>(GetWorld(), WO.Object);
		NewPool->Populate(10);
		PoolMap.Add(WO.Object, NewPool);
	}
	CalculateWeights();

}
// Called every frame
void AMovingObjectSpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AMovingObjectSpawner::CheckSpawn(float DeltaTime)
{
	if (SpawnTimer >= SpawnRateInSeconds)
	{
		float offset = FMath::FRandRange(-SpawnWidth/2, SpawnWidth/2);
		FVector perpVec = FVector::CrossProduct(FVector::UpVector, ObstacleTravelDirection.GetSafeNormal());
		FVector position = GetActorLocation() + (perpVec * offset);
		FVector overShoot = ObstacleTravelDirection.GetSafeNormal() * (SpawnTimer - SpawnRateInSeconds) * DeafultObjectSpeed;
		Spawn(position + overShoot);
		SpawnTimer -= SpawnRateInSeconds;
	}
	SpawnTimer += DeltaTime;
}
void AMovingObjectSpawner::EnqueueObject(TObjectPtr<AMovingDirectionalObject> obj)
{
	PoolMap[obj->GetClass()]->Enqueue(obj);
}
void AMovingObjectSpawner::Spawn(FVector Position)
{
	TObjectPtr<AMovingDirectionalObject> NewObstacle = PoolMap[GetClassToSpawn()]->Pop();
	ActiveObjects.Add(NewObstacle);
	if (DeafultObjectSpeed == 0)
	{
		NewObstacle->Set(Position, ObstacleTravelDirection.GetSafeNormal());
	}
	else
	{
		NewObstacle->Set(Position, ObstacleTravelDirection.GetSafeNormal(), CurrentObjectSpeed);
	}
}

