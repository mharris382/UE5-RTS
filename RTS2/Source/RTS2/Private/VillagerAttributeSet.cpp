// Fill out your copyright notice in the Description page of Project Settings.


#include "VillagerAttributeSet.h"
#include "Net/UnrealNetwork.h"

UVillagerAttributeSet::UVillagerAttributeSet()
{
}

void UVillagerAttributeSet::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME_CONDITION_NOTIFY(UVillagerAttributeSet, Energy, COND_None, REPNOTIFY_Always);
}

void UVillagerAttributeSet::OnRep_Energy(const FGameplayAttributeData& OldEnergy)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UVillagerAttributeSet, Energy, OldEnergy);
}

void UVillagerAttributeSet::OnRep_JobEfficiency(const FGameplayAttributeData& OldJobEfficiency)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UVillagerAttributeSet, JobEfficiency, OldJobEfficiency);
}
