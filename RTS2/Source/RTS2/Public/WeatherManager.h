// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "WeatherManager.generated.h"

class AStaticMeshActor;

UCLASS()
class RTS2_API AWeatherManager : public AActor
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere, Category = "Ocean")
	TObjectPtr<AActor> OceanWaterPlane;

	UPROPERTY(EditAnywhere, Category = "Sky")
	TObjectPtr<AActor> FogFacade;
	
	
public:	
	// Sets default values for this actor's properties
	AWeatherManager();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ocean")
	float WaterHeightOffset = 0;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Ocean")
	float MinWaterHeight = -270;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Ocean")
	float MaxWaterHeight = -45;
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
private:

	void MoveStaticMeshesToFollowPlayer() const;
	
	float defaultWaterPlaneZ = -130;
	float defaultFogFacadeZ = -135;
};
