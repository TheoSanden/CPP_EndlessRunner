// Copyright Epic Games, Inc. All Rights Reserved.

#include "EndlessRunnerGameMode.h"
#include "MovableCharacter.h"
#include "Kismet/GameplayStatics.h"	
#include "Engine/DataAsset.h"
#include "GameFramework/PlayerController.h"
#include "GameFramework/PlayerStart.h"
#include "UObject/ConstructorHelpers.h"

AEndlessRunnerGameMode::AEndlessRunnerGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<AMovableCharacter> PlayerPawnBPClass(TEXT("/Game/Characters/BP_Player"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		PlayerClass = PlayerPawnBPClass.Class;
		DefaultPawnClass = NULL;
	}

	/*static ConstructorHelpers::FObjectFinder<UInputMappingContext> PlayerOneInput(TEXT("/Game/ThirdPerson/Input/IMC_PlayerOne.IMC_PlayerOne"));
	static ConstructorHelpers::FObjectFinder<UInputMappingContext> PlayerTwoInput(TEXT("/Game/ThirdPerson/Input/IMC_PlayerTwo.IMC_PlayerTwo"));

	if(PlayerOneInput.Object == NULL || PlayerTwoInput.Object ==  NULL)
	{
		UE_LOG(LogTemp, Warning, TEXT("Input mappings not found"))
		
	}
	else
	{
		PlayerInputMappings.Add(PlayerOneInput.Object);
		PlayerInputMappings.Add(PlayerTwoInput.Object);
	}*/

	const wchar_t* DataAssetPath = TEXT("/Game/Input/DA_PlayerInput.DA_PlayerInput");
	static ConstructorHelpers::FObjectFinder<UDA_PlayerInput>DA_PlayerInput(DataAssetPath);

	if (DA_PlayerInput.Succeeded())
	{
		PlayerInputDataAsset = DA_PlayerInput.Object;
	}

	DataAssetPath = TEXT("/Game/Input/BP_LocalMultiplayerInputManager");
	static ConstructorHelpers::FClassFinder<APawn>LocalMultiplayerInputManagerReference(DataAssetPath);

	if (LocalMultiplayerInputManagerReference.Class != NULL)
	{
		LocalMultiplayerInputManager = LocalMultiplayerInputManagerReference.Class;
	}
}
void AEndlessRunnerGameMode::BeginPlay()
{
	Super::BeginPlay();
	InitializePlayerInput();
}

void AEndlessRunnerGameMode::InitializePlayerInput()
{
	TArray<AActor*> PlayerStarts;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(),APlayerStart::StaticClass(), PlayerStarts);

	APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	LMIM_Instance = GetWorld()->SpawnActor<ALocalMultiplayerInputManager>(LocalMultiplayerInputManager, PlayerStarts[2]->GetActorLocation(), PlayerStarts[2]->GetActorRotation());

	TArray<AMovableCharacter*> Players;

	for(AActor* start : PlayerStarts)
	{
		AMovableCharacter* character = GetWorld()->SpawnActor<AMovableCharacter>(PlayerClass, start->GetActorLocation(), start->GetActorRotation());
		Players.Add(character);
	}

	LMIM_Instance->RegisterPlayers(Players[0],Players[1]);
	PlayerController->Possess(LMIM_Instance);
	LMIM_Instance->SetUpInputMappingContext(nullptr,PlayerController);
}

