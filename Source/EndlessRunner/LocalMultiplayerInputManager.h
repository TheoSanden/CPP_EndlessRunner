// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DA_PlayerInput.h"
#include "InputActionValue.h"
#include "MovableCharacter.h"
#include "GameFramework/Pawn.h"
#include "LocalMultiplayerInputManager.generated.h"

UCLASS()
class ENDLESSRUNNER_API ALocalMultiplayerInputManager : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ALocalMultiplayerInputManager();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputMappingContext* DefaultMappingContext;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	UPROPERTY()
	UDA_PlayerInput* PlayerInputDataAsset;
	UPROPERTY()
	UInputComponent* GlobalInputComponent;

	UPROPERTY()
	AMovableCharacter* P1;
	UPROPERTY()
	AMovableCharacter* P2;
	// Called to bind functionality to input
	void SetUpInputMappingContext(UInputMappingContext* InputMappingContext, APlayerController* _Controller);
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	virtual void RegisterPlayers(AMovableCharacter* PlayerOne, AMovableCharacter* PlayerTwo);

	void P1_Move(const FInputActionValue& Value);
	void P2_Move(const FInputActionValue& Value);

	void P1_Jump();
	void P1_StopMove();

	void P2_Jump();
	void P2_StopMove();

};
