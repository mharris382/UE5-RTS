// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerPawnStateComponent.h"
#include "RTS_PlayerPawn.h"
#include "EnhancedInputSubsystems.h"

// Sets default values for this component's properties
UPlayerPawnStateComponent::UPlayerPawnStateComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UPlayerPawnStateComponent::BeginPlay()
{
	Super::BeginPlay();

	
	// ...
}



// Called every frame
void UPlayerPawnStateComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UPlayerPawnStateComponent::EnterState()
{
	ARTS_PlayerPawn* pawn = Cast<ARTS_PlayerPawn>(GetOwner());
	if (APlayerController* PC = Cast<APlayerController>(pawn->Controller))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem< UEnhancedInputLocalPlayerSubsystem>(PC->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(StateMappingContext, 1);
			OnStateEntered(Subsystem);
		}
	}
}

void UPlayerPawnStateComponent::ExitState()
{
	ARTS_PlayerPawn* pawn = Cast<ARTS_PlayerPawn>(GetOwner());
	if (APlayerController* PC = Cast<APlayerController>(pawn->Controller))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem< UEnhancedInputLocalPlayerSubsystem>(PC->GetLocalPlayer()))
		{
			Subsystem->RemoveMappingContext(StateMappingContext);
			OnStateExited(Subsystem);
		}
	}
}



//void UPlayerPawnStateComponent::OnStateEntered(UEnhancedInputLocalPlayerSubsystem* inputSubsystem)
//{
//}
//
//void UPlayerPawnStateComponent::OnStateExited(UEnhancedInputLocalPlayerSubsystem* inputSubsystem)
//{
//}