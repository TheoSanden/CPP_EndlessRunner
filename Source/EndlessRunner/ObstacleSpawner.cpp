// Fill out your copyright notice in the Description page of Project Settings.


#include "ObstacleSpawner.h"

// Sets default values
AObstacleSpawner::AObstacleSpawner()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

AObstacleSpawner::~AObstacleSpawner()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	delete ObstaclePooler;
}
// Called when the game starts or when spawned
void AObstacleSpawner::BeginPlay()
{
	Super::BeginPlay();
	ObstaclePooler = new ActorPooler<AMovingDirectionalObject>(GetWorld(), ObstacleToSpawn);
	ObstaclePooler->Populate(30);
}

void AObstacleSpawner::Spawn(FVector Position)
{
	//Move this code to the objectpooler later
	//TObjectPtr<AMovingDirectionalObject> NewObstacle = GetWorld()->SpawnActor<AMovingDirectionalObject>(ObstacleToSpawn, FVector(0,0,0), FRotator(0, 0, 0));
	//ActiveObstacles.Add(NewObstacle);
	//AMovingDirectionalObject* NewObstacle = GetWorld()->SpawnActor<AMovingDirectionalObject>(ObstacleToSpawn, FVector(0, 0, 0), FRotator(0, 0, 0));
	//NewObstacle->Set(GetActorLocation(), ObstacleTravelDirection.GetSafeNormal());

	TObjectPtr<AMovingDirectionalObject> NewObstacle = ObstaclePooler->Pop();
	ActiveObjects.Add(NewObstacle);
	if(DeafultObjectSpeed == 0)
	{
		NewObstacle->Set(Position, ObstacleTravelDirection.GetSafeNormal());
	}
	else
	{
		NewObstacle->Set(Position, ObstacleTravelDirection.GetSafeNormal(), DeafultObjectSpeed);
	}
}
void AObstacleSpawner::CheckSpawn(float DeltaTime)
{
	//Move the spawned object forward according to the difference in time over spawnrateinseconds
	if(SpawnTimer >= SpawnRateInSeconds)
	{
		FVector position = GetActorLocation();
		FVector overShoot = ObstacleTravelDirection.GetSafeNormal() *  (SpawnTimer-SpawnRateInSeconds) * DeafultObjectSpeed;
		Spawn(position + overShoot);
		SpawnTimer -= SpawnRateInSeconds;
	}
	SpawnTimer += DeltaTime;
}

// Called every frame
void AObstacleSpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	CheckSpawn(DeltaTime);
	CheckObstacleReachEnd();
}
void AObstacleSpawner::CheckObstacleReachEnd()
{
	if(ActiveObjects.IsEmpty())
	{
		return;
	}
	FVector delta = (GetActorLocation()) - ActiveObjects[0]->GetActorLocation();
	if (delta.Length() >= KillDistance)
	{
		TObjectPtr<AMovingDirectionalObject> obj = ActiveObjects[0];
		ActiveObjects.RemoveAt(0,1,true);
		ObstaclePooler->Enqueue(obj);
	}
}

void AObstacleSpawner::UpdateObjectSpeed(float MovementSpeed)
{
	for(TObjectPtr<AMovingDirectionalObject> obj: ActiveObjects)
	{
		obj->OverrideMovementSpeed(MovementSpeed);
	}
}

