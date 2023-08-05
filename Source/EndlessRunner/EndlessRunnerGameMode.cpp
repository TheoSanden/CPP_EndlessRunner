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
		LocalMultiplayerInputManagerClass = LocalMultiplayerInputManagerReference.Class;
	}
	///Script/Engine.Blueprint'/Game/Ui/BP_ScoreTracker.BP_ScoreTracker'


	DataAssetPath = TEXT("/Game/Ui/BP_ScoreTracker");
	static ConstructorHelpers::FClassFinder<AActor>ScoreTrackerReference(DataAssetPath);

	if (ScoreTrackerReference.Class != NULL)
	{
		ScoreTrackerClass = ScoreTrackerReference.Class;
	}
}
void AEndlessRunnerGameMode::BeginPlay()
{
	Super::BeginPlay();
	ScoreTracker = GetWorld()->SpawnActor<AScoreTracker>(ScoreTrackerClass, FVector::Zero(), FRotator::ZeroRotator);
	InitializePlayerInput();
}

void AEndlessRunnerGameMode::InitializePlayerInput()
{
	UGameplayStatics::GetAllActorsOfClass(GetWorld(),APlayerStart::StaticClass(), PlayerStarts);

	APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	LMIM_Instance = GetWorld()->SpawnActor<ALocalMultiplayerInputManager>(LocalMultiplayerInputManagerClass, PlayerStarts[2]->GetActorLocation(), PlayerStarts[2]->GetActorRotation());

	TArray<AMovableCharacter*> Players;

	for(AActor* start : PlayerStarts)
	{
		AMovableCharacter* character = GetWorld()->SpawnActor<AMovableCharacter>(PlayerClass, start->GetActorLocation(), start->GetActorRotation());
		Players.Add(character);
	}

	LMIM_Instance->RegisterPlayers(Players[0],Players[1]);
	PlayerController->Possess(LMIM_Instance);
	LMIM_Instance->SetUpInputMappingContext(nullptr,PlayerController);

	ScoreTracker->UpdatePlayerHealth(0, 3);
	ScoreTracker->UpdatePlayerHealth(1, 3);
}

void AEndlessRunnerGameMode::RespawnPlayer(AMovableCharacter* Character)
{
	int playerIndex = (Character->GetUniqueID() == LMIM_Instance->P1->GetUniqueID()) ? 0 : (Character->GetUniqueID() == LMIM_Instance->P2->GetUniqueID() ? 1 : 99);
	if (playerIndex == 99) { return; }
	Character->SetActorLocation(PlayerStarts[playerIndex]->GetActorLocation());

	Character->CurrentLives -= 1;
	Character->ResetVelocity();

	ScoreTracker->UpdatePlayerHealth(playerIndex, Character->CurrentLives);



	//Maybe move
	float PointsLossAmount = 25;
	ScoreTracker->ChangePlayerScore(playerIndex,-PointsLossAmount);
}
void AEndlessRunnerGameMode::ChangePlayerScore(AMovableCharacter* Character, int Amount)
{
	int playerIndex = (Character->GetUniqueID() == LMIM_Instance->P1->GetUniqueID()) ? 0 : (Character->GetUniqueID() == LMIM_Instance->P2->GetUniqueID() ? 1 : 99);
	if (playerIndex == 99) { return; }

	ScoreTracker->ChangePlayerScore(playerIndex, Amount);
}

