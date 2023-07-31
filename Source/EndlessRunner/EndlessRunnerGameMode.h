// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "EndlessRunnerCharacter.h"

#include "EndlessRunnerGameMode.generated.h"

class UInputMappingContext;

UCLASS(minimalapi)
class AEndlessRunnerGameMode : public AGameModeBase
{
	GENERATED_BODY()
	int PlayerInputContextIndex = 0;
protected:
	UPROPERTY()
	UInputMappingContext* PlayerOneInputMappingContext;
	UPROPERTY()
	UInputMappingContext* PlayerTwoInputMappingContext;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Classes)
	TSubclassOf<APawn> PlayerToSpawn;

public:

	virtual void BeginPlay() override;
	//0 == 1 
	UInputMappingContext* GetInputMappingContext();

	void SpawnPlayer();
	
	AEndlessRunnerGameMode();
};



