// Fill out your copyright notice in the Description page of Project Settings.


#include "RTSPlayerController.h"
#include "RTSPlayerState.h"

ARTSPlayerController::ARTSPlayerController()
{
}

void ARTSPlayerController::ReturnToDefaultState()
{
	ChangeState(DefaultState);
}

void ARTSPlayerController::ChangeState(URTSPlayerState* newState)
{
	if(CurrentState)
	{
		CurrentState->OnStateExit();
		for(URTSPlayerState* subState : SubStates)
		{
			subState->OnStateExit();
		}
	}
	CurrentState = newState;
	if(CurrentState)
	{
		CurrentState->OnStateEnter();
	}
	SubStates.Empty();
}

void ARTSPlayerController::AddSubState(URTSPlayerState* newSubState)
{
	if(newSubState)
	{
		SubStates.Add(newSubState);
		newSubState->OnStateEnter();
	}
}

void ARTSPlayerController::RemoveSubState(URTSPlayerState* newSubState)
{
	if(newSubState)
	{
		SubStates.Remove(newSubState);
		newSubState->OnStateExit();
	}
}

void ARTSPlayerController::BeginPlay()
{
	Super::BeginPlay();
	DefaultState = NewObject<URTSPlayerState>(this, DefaultPlayerStateClass);
	ReturnToDefaultState();
}

void ARTSPlayerController::OnPossess(APawn* aPawn)
{
	Super::OnPossess(aPawn);
}


