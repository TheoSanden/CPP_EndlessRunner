// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/CapsuleComponent.h"
#include "Components/StaticMeshComponent.h"
#include "InputActionValue.h"
#include "GameFramework/Actor.h"
#include "MovableCharacter.generated.h"

UCLASS()
class ENDLESSRUNNER_API AMovableCharacter : public AActor
{
	GENERATED_BODY()

public:	
	// Sets default values for this actor's properties
	AMovableCharacter();
protected:

	UPROPERTY()
	bool hasPressedJump;
	UPROPERTY()
	FRotator StartRotation;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	UStaticMeshComponent* MeshComponent;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	UCapsuleComponent* CapsuleComponent;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Movement")
	float MovementSpeed = 2;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Movement")
	float JumpForce = 3000;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Collision")
	float GroundTraceLength;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Collision")
	TArray<TEnumAsByte<EObjectTypeQuery>> GroundTraceObjectQueryType;
public:
	const float BaseLives = 3;
	float CurrentLives;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	bool GroundCheck();

	bool IsDead = false;
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	void SetRotationalAxis(FRotator Rotation);
	void Move(const FInputActionValue& Value);
	void StopMove();
	void StopJump();
	void Jump();
	void ResetVelocity();
	void SetDeadState(bool DeadState);
};
