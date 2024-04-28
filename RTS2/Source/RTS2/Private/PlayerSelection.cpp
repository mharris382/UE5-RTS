// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerSelection.h"

// Sets default values for this component's properties
UPlayerSelection::UPlayerSelection()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


bool UPlayerSelection::SetFocusedActor(AActor* selectedActor)
{
	if(FocusedActor != selectedActor)
	{
		FocusedActor = selectedActor;
		FocusedActorChanged(selectedActor);
		OnFocusedActorChanged.Broadcast(selectedActor);
	}
	return true;
}

void UPlayerSelection::ClearFocusedActor()
{
	if(FocusedActor)
	{
		FocusedActor = nullptr;
		FocusedActorChanged(nullptr);
		OnFocusedActorChanged.Broadcast(nullptr);
	}
}

void UPlayerSelection::OnPawnDragged(APawn* draggedPawn, FVector dragEndPosition, AActor* dragEndActor, TArray<FVector> pathPoints)
{
	if(!draggedPawn)
		return;
	SetFocusedActor(draggedPawn);
	APlayerController* playerController = Cast<APlayerController>(draggedPawn->GetController());
	APawn* playerPawn = playerController ? playerController->GetPawn() : nullptr;
	if(dragEndActor && dragEndActor != playerPawn)
	{
		OnPawnDraggedToActor(draggedPawn, dragEndActor);
	}
	else
	{
		OnPawnDraggedToLocation(draggedPawn, dragEndPosition);
	}
	
}

void UPlayerSelection::FocusedActorChanged_Implementation(AActor* actor)
{
}

void UPlayerSelection::OnPawnDraggedToActor_Implementation(APawn* draggedPawn, AActor* draggedOntoActor)
{
}


void UPlayerSelection::OnPawnDraggedToLocation_Implementation(APawn* draggedPawn, FVector dragEndPosition)
{
}

// Called when the game starts
void UPlayerSelection::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UPlayerSelection::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

