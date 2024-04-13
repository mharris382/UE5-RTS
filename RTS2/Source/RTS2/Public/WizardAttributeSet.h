// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AgentAttributeSet.h"
#include "AbilitySystemComponent.h"
#include "AttributeSet.h"
#include "WizardAttributeSet.generated.h"

/**
 * 
 */
UCLASS()
class RTS2_API UWizardAttributeSet : public UAgentAttributeSet
{
	GENERATED_BODY()
public:
	UWizardAttributeSet();

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
	
	UPROPERTY(BlueprintReadOnly, Category = "Attributes", ReplicatedUsing=OnRep_Mana)
	FGameplayAttributeData Mana;
	
	ATTRIBUTE_ACCESSORS(UWizardAttributeSet, Mana);

	
	UFUNCTION()
	virtual void OnRep_Mana(const FGameplayAttributeData& OldMana);
};
