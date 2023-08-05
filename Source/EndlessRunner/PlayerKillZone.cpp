// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerKillZone.h"
#include "MovableCharacter.h"
#include "EndlessRunnerGameMode.h"

// Sets default values
APlayerKillZone::APlayerKillZone()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	//CollisionMesh = CreateDefaultSubobject<UStaticMeshComponent>("StaticMesh");
	BoxCollider = CreateDefaultSubobject<UBoxComponent>("KillCollider");
}

// Called when the game starts or when spawned
void APlayerKillZone::BeginPlay()
{
	Super::BeginPlay();
	BoxCollider->SetGenerateOverlapEvents(true);
	BoxCollider->OnComponentBeginOverlap.AddDynamic(this,&APlayerKillZone::OnOverlap);
}

// Called every frame
void APlayerKillZone::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void APlayerKillZone::OnOverlap(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if(AMovableCharacter* Character = CastChecked<AMovableCharacter>(OtherActor))
	{
		Character->GetUniqueID();
		if(AEndlessRunnerGameMode* GameMode = CastChecked<AEndlessRunnerGameMode>(GetWorld()->GetAuthGameMode()))
		{
			GameMode->RespawnPlayer(Character);
		}
	}
}

