// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Agent.h"
#include "AbilitySystemInterface.h"
#include "GameplayEffectTypes.h"
#include "RTS2/RTS2.h"

#include "Wizard.generated.h"



UCLASS(config=Game)
class RTS2_API AWizard : public AAgent, public IAbilitySystemInterface
{
	GENERATED_BODY()


	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Ability", meta = (AllowPrivateAccess = "true"))
	class UWizardAbilitySystemComponent* AbilitySystemComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Ability", meta = (AllowPrivateAccess = "true"))
	class UWizardAttributeSet* AttributeSet;
	
public:
	// Sets default values for this pawn's properties
	AWizard();

	virtual class UAbilitySystemComponent* GetAbilitySystemComponent() const override;

	virtual void InitializeAttributes();
	virtual void GiveAbilities();

	virtual void PossessedBy(AController* NewController) override;
	virtual void OnRep_PlayerState() override;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Ability")
	TSubclassOf<class UGameplayEffect> DefaultAttributeEffect;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Ability")
	TArray<TSubclassOf<class UWizardGameplayAbility>> DefaultAbilities;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Ability")
	TObjectPtr<AActor> GameplayOwner;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Ability")
	float WizardLevel = 1;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Magic")
	EWizardDiscipline MagicalDiscipline = EWizardDiscipline::Novice;
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	virtual UAbilitySystemComponent* GetAgentAbilitySystemComponent() const override;

	UFUNCTION(BlueprintCallable, Category = "Magic")
	bool TrySetMagicalDiscipline(EWizardDiscipline NewDiscipline);	

	UFUNCTION(BlueprintNativeEvent, Category = "Magic")
	void SetMagicalDiscipline(EWizardDiscipline NewDiscipline);

	void SetMagicalDiscipline_Implementation(EWizardDiscipline NewDiscipline);
};
