// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
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
	FRotator StartRotation;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	UStaticMeshComponent* MeshComponent;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Movement")
	float MovementSpeed;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Movement")
	float JumpForce;
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	void SetRotationalAxis(FRotator Rotation);
	void Move(const FInputActionValue& Value);
	void StopMove();
	void Jump();

};
