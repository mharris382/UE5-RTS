﻿// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Agent.h"
#include "AbilitySystemInterface.h"
#include "GameplayEffectTypes.h"
#include "Villager.generated.h"

UCLASS(config=Game)
class RTS2_API AVillager : public AAgent
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Ability", meta = (AllowPrivateAccess = "true"))
	class UVillagerAbilitySystemComponent* AbilitySystemComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Ability", meta = (AllowPrivateAccess = "true"))
	class UVillagerAttributeSet* AttributeSet;
	
public:
	// Sets default values for this pawn's properties
	AVillager();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	virtual UAbilitySystemComponent* GetAgentAbilitySystemComponent() const override;
};
