// Fill out your copyright notice in the Description page of Project Settings.


#include "WizardAttributeSet.h"
#include "Net/UnrealNetwork.h"

UWizardAttributeSet::UWizardAttributeSet()
{
}

void UWizardAttributeSet::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME_CONDITION_NOTIFY(UWizardAttributeSet, Mana, COND_None, REPNOTIFY_Always);
}

void UWizardAttributeSet::OnRep_Mana(const FGameplayAttributeData& OldMana)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UWizardAttributeSet, Mana, OldMana);
}
