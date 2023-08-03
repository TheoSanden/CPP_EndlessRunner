// Fill out your copyright notice in the Description page of Project Settings.


#include "MovableCharacter.h"
#include "Kismet/KismetMathLibrary.h"

// Sets default values
AMovableCharacter::AMovableCharacter()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(FName("Mesh"));

}
// Called when the game starts or when spawned
void AMovableCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	
}
// Called every frame
void AMovableCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AMovableCharacter::SetRotationalAxis(FRotator Rotation)
{
	SetActorRotation(Rotation);
	StartRotation = Rotation;
}
void AMovableCharacter::Move(const FInputActionValue& Value)
{
	FVector2D Input = Value.Get<FVector2D>();

	FVector Transformation = UKismetMathLibrary::GetRightVector(StartRotation) * Input.X;
	AddActorLocalOffset(Transformation);

//	FRotator Rotation = UKismetMathLibrary::MakeRotFromXY();
}
void AMovableCharacter::StopMove()
{

}
void AMovableCharacter::Jump()
{

}
