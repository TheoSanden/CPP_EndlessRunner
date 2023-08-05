// Fill out your copyright notice in the Description page of Project Settings.


#include "MovingDirectionalObject.h"
#include "Components/StaticMeshComponent.h"

// Sets default values
AMovingDirectionalObject::AMovingDirectionalObject()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	/*
	FrontAttachmentPoint = CreateDefaultSubobject<UArrowComponent>(TEXT("Front Attachment Point"));
	AssAttachmentPoint = CreateDefaultSubobject<UArrowComponent>(TEXT("Ass Attachment Point"));
	FrontAttachmentPoint->SetupAttachment(RootComponent);
	AssAttachmentPoint->SetupAttachment(RootComponent);
	*/
	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(FName("Main Mesh"));
}
// Called when the game starts or when spawned
void AMovingDirectionalObject::BeginPlay()
{
	Super::BeginPlay();	
}
// Called every frame
void AMovingDirectionalObject::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	UpdateMovement(DeltaTime);
}
void AMovingDirectionalObject::UpdateMovement(float DeltaTime)
{
	if (TravelDirection.IsNearlyZero()) 
	{
		return; 
	}
	UE_LOG(LogTemp, Warning, TEXT("Trying to move"));

	FVector OffSet = TravelDirection * BaseMovementSpeed * DeltaTime;
	AddActorLocalOffset(OffSet);
}
void AMovingDirectionalObject::Set(FVector Position, FVector Direction)
{
	SetActorLocation(Position);
	TravelDirection = Direction;
}
void AMovingDirectionalObject::Set(FVector Position, FVector Direction, float OverrideSpeed)
{
	Set(Position,Direction);
	BaseMovementSpeed = OverrideSpeed;
}
void AMovingDirectionalObject::Active(bool value)
{
	bIsActive = value;
	if(value)
	{
	}
	else
	{
		TravelDirection = FVector(0,0,0);
	}
}
void AMovingDirectionalObject::OverrideMovementSpeed(float OverrideSpeed)
{
	BaseMovementSpeed = OverrideSpeed;
}

