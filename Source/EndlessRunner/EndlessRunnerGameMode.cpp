// Copyright Epic Games, Inc. All Rights Reserved.

#include "EndlessRunnerGameMode.h"
#include "InputMappingContext.h"
#include "EndlessRunnerCharacter.h"
#include "UObject/ConstructorHelpers.h"

AEndlessRunnerGameMode::AEndlessRunnerGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
	
	const wchar_t* DataAssetPath = TEXT("/Game/Content/Input/IMC_PlayerOne.IMC_PlayerOne");
    static ConstructorHelpers::FObjectFinder<UInputMappingContext>P1IMC(DataAssetPath);
	
	if (P1IMC.Succeeded())
	{
		PlayerOneInputMappingContext = P1IMC.Object;
	}
	else
	{
		UE_LOG(LogTemp,Warning, TEXT("Cannot find Player One Input Context"));
	}

	DataAssetPath = TEXT("/Game/Content/Input/IMC_PlayerTwo.IMC_PlayerTwo");
    static ConstructorHelpers::FObjectFinder<UInputMappingContext>P2IMC(DataAssetPath);
	if (P2IMC.Succeeded())
	{
		PlayerTwoInputMappingContext = P2IMC.Object;
	}
	else
	{
		UE_LOG(LogTemp,Warning, TEXT("Cannot find Player Two Input Context"));
	}
}
UInputMappingContext* AEndlessRunnerGameMode::GetInputMappingContext()
{
	switch(PlayerInputContextIndex)
	{
	    default:
	    	PlayerInputContextIndex++;
		case 0:
			return PlayerOneInputMappingContext;
		case 1:
			return PlayerTwoInputMappingContext;
	}
}

