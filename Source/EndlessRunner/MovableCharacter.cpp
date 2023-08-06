// Fill out your copyright notice in the Description page of Project Settings.


#include "MovableCharacter.h"
#include "Components/CapsuleComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/KismetSystemLibrary.h"


// Sets default values
AMovableCharacter::AMovableCharacter()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(FName("Mesh"));
	CapsuleComponent = CreateDefaultSubobject<UCapsuleComponent>(FName("CapsuleCollider"));
	CapsuleComponent->SetupAttachment(MeshComponent);
}
// Called when the game starts or when spawned
void AMovableCharacter::BeginPlay()
{
	Super::BeginPlay();
	CurrentLives = BaseLives;
	
}
void AMovableCharacter::SetDeadState(bool DeadState)
{
	IsDead = DeadState;
	SetActorHiddenInGame(DeadState);
	CapsuleComponent->SetCollisionEnabled((DeadState)? ECollisionEnabled::NoCollision: ECollisionEnabled::QueryOnly);
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

	FVector Transformation = UKismetMathLibrary::GetRightVector(StartRotation) * Input.X * MovementSpeed;
	AddActorLocalOffset(Transformation);

//	FRotator Rotation = UKismetMathLibrary::MakeRotFromXY();
}
void AMovableCharacter::StopMove()
{

}
void AMovableCharacter::Jump()
{
	if (!GroundCheck() || hasPressedJump) { return; }
	hasPressedJump = true;

	MeshComponent->SetAllPhysicsLinearVelocity(FVector::Zero(), false);
	MeshComponent->AddImpulse(FVector::UpVector * JumpForce);
}
void AMovableCharacter::StopJump()
{
	hasPressedJump = false;
}
bool AMovableCharacter::GroundCheck()
{

	const FVector Start = GetActorLocation() + (-FVector::UpVector * CapsuleComponent->GetScaledCapsuleHalfHeight()- 0.1f);
	const FVector End = Start + (-FVector::UpVector * GroundTraceLength);

	TArray<AActor*> ActorsToIgnore;
	ActorsToIgnore.Add(this);

	FHitResult HitResult;

	float Radius = 5.0f;

	UKismetSystemLibrary::SphereTraceSingleForObjects
	(
		GetWorld(),
		Start,
		End,
		Radius,
		GroundTraceObjectQueryType,
		false,
		ActorsToIgnore,
		EDrawDebugTrace::ForDuration,
		HitResult,
		true,
		FColor::Red,
		FColor::Green,
		1
	);
	return HitResult.bBlockingHit;
}
void AMovableCharacter::ResetVelocity()
{
	MeshComponent->SetPhysicsLinearVelocity(FVector::ZeroVector);
}
