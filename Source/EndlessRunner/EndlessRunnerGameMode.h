// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "InputMappingContext.h"
#include "MovableCharacter.h"
#include "DA_PlayerInput.h"
#include "GameFramework/GameModeBase.h"
#include "LocalMultiplayerInputManager.h"
#include "EndlessRunnerGameMode.generated.h"

class UInputMappingContext;

UCLASS(minimalapi)
class AEndlessRunnerGameMode : public AGameModeBase
{
	GENERATED_BODY()

	UPROPERTY()
	TSubclassOf<AMovableCharacter> PlayerClass;

	UPROPERTY()
	TSubclassOf<ALocalMultiplayerInputManager> LocalMultiplayerInputManager;

	UPROPERTY()
		ALocalMultiplayerInputManager* LMIM_Instance;
protected:

	UPROPERTY()
	UDA_PlayerInput* PlayerInputDataAsset;

	UPROPERTY()
		int CharacterBindingIndex = 0;

	virtual void BeginPlay() override;
public:

	AEndlessRunnerGameMode();

	void InitializePlayerInput();
};



