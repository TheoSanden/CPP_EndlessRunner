// Fill out your copyright notice in the Description page of Project Settings.


#include "CollisionPointComponent.h"
#include "MovableCharacter.h"
#include "EndlessRunnerGameMode.h"
// Sets default values for this component's properties
UCollisionPointComponent::UCollisionPointComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	BoxCollider = CreateDefaultSubobject<UBoxComponent>(FName("BoxCollider"));
	BoxCollider->SetupAttachment(this);
	// ...
}


// Called when the game starts
void UCollisionPointComponent::BeginPlay()
{
	Super::BeginPlay();

	/*TArray<UStaticMeshComponent*> StaticComps;
	GetOwner()->GetComponents<UStaticMeshComponent>(StaticComps);
	BoxCollider->SetupAttachment(StaticComps[1]);*/
	BoxCollider->SetGenerateOverlapEvents(true);
	BoxCollider->OnComponentBeginOverlap.AddDynamic(this, &UCollisionPointComponent::OnOverlap);
	BoxCollider->OnComponentEndOverlap.AddDynamic(this, &UCollisionPointComponent::OnOverlapEnd);
	// ...
}


// Called every frame
void UCollisionPointComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UCollisionPointComponent::OnOverlap(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OverlappedCharacters.Contains(OtherActor->GetUniqueID())) { return; }
	if (AMovableCharacter* Character = Cast<AMovableCharacter>(OtherActor))
	{
		Character->GetUniqueID();
		if (AEndlessRunnerGameMode* GameMode = CastChecked<AEndlessRunnerGameMode>(GetWorld()->GetAuthGameMode()))
		{
			GameMode->ChangePlayerScore(Character, PointGain);
			OverlappedCharacters.Add(Character->GetUniqueID());
		}
	}
}

void UCollisionPointComponent::OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	OverlappedCharacters.Remove(OtherActor->GetUniqueID());
}

