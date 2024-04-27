// Fill out your copyright notice in the Description page of Project Settings.


#include "WeatherManager.h"
#include "Kismet/KismetMathLibrary.h"
// Sets default values
AWeatherManager::AWeatherManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AWeatherManager::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AWeatherManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	MoveStaticMeshesToFollowPlayer();
}

void AWeatherManager::MoveStaticMeshesToFollowPlayer() const
{
	APlayerController* pc = GetWorld()->GetFirstPlayerController();
	if(!pc)return;
	APawn* pawn = pc->GetPawn();
	if(!pawn)return;
	FVector location = pawn->GetActorLocation();

	location.Z = UKismetMathLibrary::Clamp(defaultWaterPlaneZ + WaterHeightOffset, MinWaterHeight, MaxWaterHeight);
	if(OceanWaterPlane)
		OceanWaterPlane->SetActorLocation(location);

	location.Z = defaultFogFacadeZ;
	if(FogFacade)
		FogFacade->SetActorLocation(location);
}

