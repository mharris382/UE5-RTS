// Fill out your copyright notice in the Description page of Project Settings.


#include "RTSPlayerPawn.h"
#include "InputAction.h"

// Sets default values
ARTSPlayerPawn::ARTSPlayerPawn()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void ARTSPlayerPawn::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ARTSPlayerPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void ARTSPlayerPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

