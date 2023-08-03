// Fill out your copyright notice in the Description page of Project Settings.


#include "LocalMultiplayerInputManager.h"
#include "EnhancedInputComponent.h"
#include "Components/InputComponent.h"
#include "EnhancedInputSubsystems.h"

// Sets default values
ALocalMultiplayerInputManager::ALocalMultiplayerInputManager()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	const wchar_t* DataAssetPath = TEXT("/Game/Input/DA_PlayerInput.DA_PlayerInput");
	static ConstructorHelpers::FObjectFinder<UDA_PlayerInput>DA_PlayerInput(DataAssetPath);

	if (DA_PlayerInput.Succeeded())
	{
		PlayerInputDataAsset = DA_PlayerInput.Object;
	}

}

// Called when the game starts or when spawned
void ALocalMultiplayerInputManager::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ALocalMultiplayerInputManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ALocalMultiplayerInputManager::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent)) {

			EnhancedInputComponent->BindAction(PlayerInputDataAsset->P1_JumpAction, ETriggerEvent::Triggered, this, &ALocalMultiplayerInputManager::P1_Jump);

			EnhancedInputComponent->BindAction(PlayerInputDataAsset->P2_MoveAction, ETriggerEvent::Completed, this, &ALocalMultiplayerInputManager::P1_StopMove);
			//Moving
			EnhancedInputComponent->BindAction(PlayerInputDataAsset->P1_MoveAction, ETriggerEvent::Triggered, this, &ALocalMultiplayerInputManager::P1_Move);

			EnhancedInputComponent->BindAction(PlayerInputDataAsset->P2_MoveAction, ETriggerEvent::Triggered, this, &ALocalMultiplayerInputManager::P2_Move);

			EnhancedInputComponent->BindAction(PlayerInputDataAsset->P2_JumpAction, ETriggerEvent::Triggered, this, &ALocalMultiplayerInputManager::P2_Jump);

			EnhancedInputComponent->BindAction(PlayerInputDataAsset->P2_MoveAction, ETriggerEvent::Completed, this, &ALocalMultiplayerInputManager::P2_StopMove);
			//Moving
	}
}

void ALocalMultiplayerInputManager::SetUpInputMappingContext(UInputMappingContext* InputMappingContext, APlayerController* _Controller)
{
	//APlayerController* PlayerController = Cast<APlayerController>(Controller)
	if (_Controller)
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(_Controller->GetLocalPlayer()))
		{
			if (InputMappingContext == nullptr)
			{
				Subsystem->AddMappingContext(DefaultMappingContext, 0);
				return;
			}
			Subsystem->AddMappingContext(InputMappingContext, 0);
		}
	}
}

void ALocalMultiplayerInputManager::RegisterPlayers(AMovableCharacter* PlayerOne, AMovableCharacter* PlayerTwo)
{
	P1 = PlayerOne;
	P2 = PlayerTwo;
}
void ALocalMultiplayerInputManager::P1_Move(const FInputActionValue& Value)
{
	P1->Move(Value);
}
void ALocalMultiplayerInputManager::P2_Move(const FInputActionValue& Value)
{
	P2->Move(Value);
}
void ALocalMultiplayerInputManager::P1_Jump()
{
	P1->Jump();
}
void ALocalMultiplayerInputManager::P2_Jump()
{
	P2->Jump();
}
void ALocalMultiplayerInputManager::P1_StopMove()
{
	P1->StopMove();
}
void ALocalMultiplayerInputManager::P2_StopMove()
{
	P2->StopMove();
}

