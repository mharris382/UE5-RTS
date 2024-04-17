// Fill out your copyright notice in the Description page of Project Settings.


#include "BuildState.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputActionValue.h"
#include "RTSPlayerController.h"

// Sets default values for this component's properties
UBuildState::UBuildState()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UBuildState::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UBuildState::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UBuildState::BindStateActions(UEnhancedInputComponent* InputComponent)
{
	Super::BindStateActions(InputComponent);
	if(InputComponent && BuildAction)
	{
		InputComponent->BindAction(BuildAction, ETriggerEvent::Triggered, this, &UBuildState::OnBuildPressed);
	}
}


void UBuildState::OnBuildPressed_Implementation()
{
}

void UBuildState::OnCancelPressed_Implementation()
{
	APlayerController* pc = GetWorld()->GetFirstPlayerController();
	if(!pc)return;
	ARTSPlayerController* rtsPC = Cast<ARTSPlayerController>(pc);
	if(rtsPC)
	{
		rtsPC->ReturnToDefaultState();
	}
}

