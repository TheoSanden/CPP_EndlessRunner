// Fill out your copyright notice in the Description page of Project Settings.


#include "PlatformSpawner.h"
#include "UObject/ConstructorHelpers.h"

// Sets default values
APlatformSpawner::APlatformSpawner()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

void APlatformSpawner::InstantiateInitialPlatform()
{
	if (PlatformSize == 0) { return; }
	int PlatformAmount = KillDistance / (PlatformSize * 100);
	for(int i = 0; i < PlatformAmount; i++)
	{
		TObjectPtr<AMovingDirectionalObject> NewPlatform = ObstaclePooler->Pop();
		ActiveObjects.Add(NewPlatform);
		NewPlatform->Set(GetActorLocation() + ObstacleTravelDirection.GetSafeNormal() * (i * PlatformSize * 100), ObstacleTravelDirection.GetSafeNormal(), DeafultObjectSpeed);
	}
}
void APlatformSpawner::CalculatePlatformMetrics()
{
	if (DeafultObjectSpeed == 0)return;
	if(PlatformSize > 0)
	{
		SpawnRateInSeconds = (100.0f * (PlatformSize)) / DeafultObjectSpeed;
		return;
	}
	PlatformSize = 1;
	//Dont know if this is in world units or not, otherwise divide by 100
}

// Called when the game starts or when spawned
void APlatformSpawner::BeginPlay()
{
	Super::BeginPlay();
	CreatePlatformReference();
	InstantiateInitialPlatform();
}
void APlatformSpawner::CreatePlatformReference()
{
	PlatformReference = GetWorld()->SpawnActor<AMovingDirectionalObject>(ObstacleToSpawn, FVector(0, 0, 0), FRotator(0, 0, 0));
	PlatformSize = PlatformReference->GetActorScale3D().X;
	PlatformReference->SetActorHiddenInGame(true);
	PlatformReference->SetActorTickEnabled(false);
	CalculatePlatformMetrics();
}
// Called every frame
void APlatformSpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

