// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/StaticMeshComponent.h"
#include "Components/ArrowComponent.h"
#include "MovingDirectionalObject.generated.h"


UCLASS()
class ENDLESSRUNNER_API AMovingDirectionalObject : public AActor
{
	GENERATED_BODY()
	bool bIsActive;
public:
	// Sets default values for this actor's properties
	AMovingDirectionalObject();
	/*
	UPROPERTY(BluePrintReadWrite, EditAnyWhere)
		UArrowComponent* FrontAttachmentPoint;
	UPROPERTY(BluePrintReadWrite, EditAnyWhere)
		UArrowComponent* AssAttachmentPoint;
	*/
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	FVector TravelDirection;
	UPROPERTY(EditAnywhere)
	float BaseMovementSpeed = 100.0f;
	virtual void UpdateMovement(float DeltaTime);
public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	UStaticMeshComponent* MeshComponent;
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	virtual void Set(FVector Position, FVector Direction);
	virtual void Set(FVector Position, FVector Direction, float OverrideSpeed);
	virtual void OverrideMovementSpeed(float OverrideSpeed);
	virtual void Active(bool value);

	bool GetActive()
	{
		return bIsActive;
	}
};
