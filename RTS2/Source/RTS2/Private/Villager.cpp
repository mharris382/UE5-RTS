// Fill out your copyright notice in the Description page of Project Settings.


#include "Villager.h"
#include "WizardAbilitySystemComponent.h"
#include "VillagerAttributeSet.h"

// Sets default values
AVillager::AVillager()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AVillager::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AVillager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void AVillager::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

