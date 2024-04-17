// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AgentAttributeSet.h"
#include "AbilitySystemComponent.h"
#include "AttributeSet.h"
#include "VillagerAttributeSet.generated.h"

/**
 * 
 */
UCLASS()
class RTS2_API UVillagerAttributeSet : public UAgentAttributeSet
{
	GENERATED_BODY()
public:
	UVillagerAttributeSet();

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
	
	UPROPERTY(BlueprintReadOnly, Category = "Attributes", ReplicatedUsing=OnRep_Energy)
	FGameplayAttributeData Energy;

	ATTRIBUTE_ACCESSORS(UVillagerAttributeSet, Energy);

	UFUNCTION()
	virtual void OnRep_Energy(const FGameplayAttributeData& OldEnergy);

	UPROPERTY(BlueprintReadOnly, Category = "Attributes", ReplicatedUsing=OnRep_JobEfficiency)
	FGameplayAttributeData JobEfficiency;

	ATTRIBUTE_ACCESSORS(UVillagerAttributeSet, JobEfficiency);

	UFUNCTION()
	virtual void OnRep_JobEfficiency(const FGameplayAttributeData& OldJobEfficiency);
};
