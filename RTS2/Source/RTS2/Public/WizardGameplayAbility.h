// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "RTS2/RTS2.h"
#include "WizardGameplayAbility.generated.h"

/**
 * 
 */
UCLASS()
class RTS2_API UWizardGameplayAbility : public UGameplayAbility
{
	GENERATED_BODY()
public:
	UWizardGameplayAbility();

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category="Ability")
	EAbilityInputID AbilityInputID = EAbilityInputID::None;

	
};
