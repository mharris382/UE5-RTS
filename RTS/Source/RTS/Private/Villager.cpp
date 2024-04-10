// Fill out your copyright notice in the Description page of Project Settings.


#include "Villager.h"

namespace
{
	FTimerHandle EatTimerHandle;
}

AVillager::AVillager()
{

	Hat = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Hat"));
	Hat->SetupAttachment(SkeletalMesh, TEXT("headSocket"));

	Hair = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Hair"));
	Hair->SetupAttachment(SkeletalMesh);

	Tool = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Tool"));
	Tool->SetupAttachment(SkeletalMesh, TEXT("hand_rSocket"));
}

void AVillager::BeginPlay()
{
	Super::BeginPlay();


	GetWorld()->GetTimerManager().SetTimer(EatTimerHandle, this, &AVillager::Eat, EatIntervalSeconds, true);
}

void AVillager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

