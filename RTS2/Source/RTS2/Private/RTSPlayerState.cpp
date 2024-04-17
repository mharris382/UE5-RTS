// Fill out your copyright notice in the Description page of Project Settings.


#include "RTSPlayerState.h"
#include "InputAction.h"
#include "InputActionValue.h"
#include "InputMappingContext.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Engine/Engine.h"

// Sets default values for this component's properties
URTSPlayerState::URTSPlayerState()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


void URTSPlayerState::StateExit_Implementation()
{
}

// Called when the game starts
void URTSPlayerState::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}

void URTSPlayerState::OnStateEnter()
{
	APlayerController* pc = GetWorld()->GetFirstPlayerController();

	UEnhancedInputLocalPlayerSubsystem* inputSubsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(pc->GetLocalPlayer());
	if(inputSubsystem && StateMappingContext)
	{
		inputSubsystem->AddMappingContext(StateMappingContext, 0);
		
		FString message =FString::Printf(TEXT("Added Mapping Context %s"), *StateMappingContext->GetName());
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, message);
	}
	
	UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(pc->InputComponent);
	if(!hasBoundActions && EnhancedInputComponent)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, TEXT("Binding Input Actions"));
		BindStateActions(EnhancedInputComponent);
	}
	StateEnter();
}

void URTSPlayerState::OnStateExit()
{
	APlayerController* pc = GetWorld()->GetFirstPlayerController();

	UEnhancedInputLocalPlayerSubsystem* inputSubsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(pc->GetLocalPlayer());
	if(inputSubsystem && StateMappingContext)
	{
		inputSubsystem->RemoveMappingContext(StateMappingContext);
		
		inputSubsystem->AddMappingContext(StateMappingContext, 0);
		FString message =FString::Printf(TEXT("Removed Mapping Context %s"), *StateMappingContext->GetName());
	}
	StateExit();
}

void URTSPlayerState::StateEnter_Implementation()
{
}

void URTSPlayerState::OnCancelPressed_Implementation()
{
}

void URTSPlayerState::BindStateActions(UEnhancedInputComponent* InputComponent)
{
	if(hasBoundActions || !InputComponent)return;
	hasBoundActions = true;
	if(CancelAction && InputComponent)
	{
		InputComponent->BindAction(CancelAction, ETriggerEvent::Triggered, this, &URTSPlayerState::OnCancelPressed);	
	}
}

// Called every frame
void URTSPlayerState::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

