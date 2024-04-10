// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Agent.h"
#include "Villager.generated.h"

/**
 * 
 */
UCLASS()
class RTS_API AVillager : public AAgent
{
	GENERATED_BODY()
	
public:
	AVillager();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	TObjectPtr<UStaticMeshComponent> Tool;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	TObjectPtr<USkeletalMeshComponent> Hat;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	TObjectPtr<USkeletalMeshComponent> Hair;

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Timing")
	float EatIntervalSeconds = 24.0f;

public:
	virtual void Tick(float DeltaTime) override;


	UFUNCTION(BlueprintImplementableEvent, Category = "Actions")
	void Eat();
};
