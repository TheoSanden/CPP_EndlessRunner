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

