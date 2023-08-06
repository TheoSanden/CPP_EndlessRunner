// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "InputMappingContext.h"
#include "MovableCharacter.h"
#include "ScoreTracker.h"
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
	TSubclassOf<ALocalMultiplayerInputManager> LocalMultiplayerInputManagerClass;

	UPROPERTY()

	TObjectPtr<ALocalMultiplayerInputManager> LMIM_Instance;

	UPROPERTY()
	TSubclassOf<AScoreTracker> ScoreTrackerClass;

	UPROPERTY()
	AScoreTracker* ScoreTracker;

	UPROPERTY()
	TArray<AActor*> PlayerStarts;

	bool HasSavedScore = false;
protected:

	UPROPERTY()
	UDA_PlayerInput* PlayerInputDataAsset;

	UPROPERTY()
	int CharacterBindingIndex = 0;

	virtual void BeginPlay() override;
public:

	AEndlessRunnerGameMode();

	void InitializePlayerInput();
	void RespawnPlayer(AMovableCharacter* Character);
	void ChangePlayerScore(AMovableCharacter* Character, int Amount);
};



