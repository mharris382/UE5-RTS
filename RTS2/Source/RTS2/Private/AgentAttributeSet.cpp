// Fill out your copyright notice in the Description page of Project Settings.


#include "AgentAttributeSet.h"

#include "Net/UnrealNetwork.h"

UAgentAttributeSet::UAgentAttributeSet()
{
}

void UAgentAttributeSet::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME_CONDITION_NOTIFY(UAgentAttributeSet, Health, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAgentAttributeSet, AttackPower, COND_None, REPNOTIFY_Always);
}

void UAgentAttributeSet::OnRep_Health(const FGameplayAttributeData& OldHealth)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAgentAttributeSet, Health, OldHealth);
}

void UAgentAttributeSet::OnRep_AttackPower(const FGameplayAttributeData& OldAttackPower)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAgentAttributeSet, AttackPower, OldAttackPower);
}

void UAgentAttributeSet::OnRep_MoveSpeed(const FGameplayAttributeData& OldMoveSpeed)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAgentAttributeSet, MoveSpeed, OldMoveSpeed);
}
