// Fill out your copyright notice in the Description page of Project Settings.


#include "Wizard.h"
#include "WizardAbilitySystemComponent.h"
#include "GameplayEffectTypes.h"
#include "Components/SkeletalMeshComponent.h"
#include "WizardAttributeSet.h"
#include "UObject/ConstructorHelpers.h"
#include "WizardGameplayAbility.h"

// Sets default values
AWizard::AWizard()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	AbilitySystemComponent = CreateDefaultSubobject<UWizardAbilitySystemComponent>("AbilitySystemComp");
	AbilitySystemComponent->SetIsReplicated(true);
	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Minimal);

	AttributeSet = CreateDefaultSubobject<UWizardAttributeSet>("Attributes");
	
}

UAbilitySystemComponent* AWizard::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

void AWizard::InitializeOwnerActor()
{
	APlayerController* pc = GetWorld()->GetFirstPlayerController();
	if(pc && pc->GetPawn())
	{
		APawn* playerPawn = pc->GetPawn();
	}
	else
	{
		WaitForPlayerPawnHandle.Invalidate();
		GetWorld()->GetTimerManager().SetTimer(WaitForPlayerPawnHandle, this,  &AWizard::CheckIfPlayerPawnExists, 0.2f, true);
	}
}

void AWizard::InitializeAttributes()
{
	if(AbilitySystemComponent && DefaultAttributeEffect)
	{
		FGameplayEffectContextHandle EffectContext = AbilitySystemComponent->MakeEffectContext();
		EffectContext.AddSourceObject(this);

		FGameplayEffectSpecHandle SpecHandle = AbilitySystemComponent->MakeOutgoingSpec(DefaultAttributeEffect, WizardLevel, EffectContext);

		if(SpecHandle.IsValid())
		{
			FActiveGameplayEffectHandle GEHandle = AbilitySystemComponent->ApplyGameplayEffectSpecToSelf(*SpecHandle.Data.Get());
		}
	}
}

void AWizard::GiveAbilities()
{
	if(HasAuthority() && AbilitySystemComponent)
	{
		for(TSubclassOf<UWizardGameplayAbility>& StartupAbility : DefaultAbilities)
		{
			AbilitySystemComponent->GiveAbility(FGameplayAbilitySpec(StartupAbility, WizardLevel, static_cast<int32>(StartupAbility.GetDefaultObject()->AbilityInputID), this));
		}
	}
}

void AWizard::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	if(!AbilitySystemComponent)return;
	
	AbilitySystemComponent->InitAbilityActorInfo(GameplayOwner ? GameplayOwner : NewController, this);
	InitializeAttributes();
	GiveAbilities();
}

void AWizard::OnRep_PlayerState()
{
	Super::OnRep_PlayerState();
	if(!AbilitySystemComponent)return;
	
	AbilitySystemComponent->InitAbilityActorInfo(GameplayOwner ? GameplayOwner : this, this);
	InitializeAttributes();
	if(AbilitySystemComponent && InputComponent)
	{
		const FGameplayAbilityInputBinds Binds("Confirm", "Cancel",
		 FTopLevelAssetPath(GetPathNameSafe(UClass::TryFindTypeSlow<UEnum>("EAbilityInputID"))),
		 static_cast<int32>(EAbilityInputID::Confirm),  static_cast<int32>(EAbilityInputID::Cancel));
		AbilitySystemComponent->BindAbilityActivationToInputComponent(InputComponent, Binds);
	}
}

// Called when the game starts or when spawned
void AWizard::BeginPlay()
{
	Super::BeginPlay();
	if(AbilitySystemComponent)
	{
		
		InitializeAttributes();
		GiveAbilities();
	}
}

// Called every frame
void AWizard::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void AWizard::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	
	// if(AbilitySystemComponent && InputComponent)
	// {
	// 	const FGameplayAbilityInputBinds Binds("Confirm", "Cancel",
	// 	 FTopLevelAssetPath(GetPathNameSafe(UClass::TryFindTypeSlow<UEnum>("EAbilityInputID"))),
	// 	 static_cast<int32>(EAbilityInputID::Confirm),  static_cast<int32>(EAbilityInputID::Cancel));
	// 	AbilitySystemComponent->BindAbilityActivationToInputComponent(InputComponent, Binds);
	// }
}

UAbilitySystemComponent* AWizard::GetAgentAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

bool AWizard::TrySetMagicalDiscipline(EWizardDiscipline NewDiscipline)
{
	if(MagicalDiscipline != EWizardDiscipline::Novice)
	{
		return false;
	}
	else
	{
		MagicalDiscipline = NewDiscipline;
		SetMagicalDiscipline(NewDiscipline);
		return true;
	}
}

void AWizard::SetMagicalDiscipline_Implementation(EWizardDiscipline NewDiscipline)
{
	
}

//wait for player pawn to exist and assign owner actor to ability system component
void AWizard::CheckIfPlayerPawnExists()
{
	APlayerController* pc = GetWorld()->GetFirstPlayerController();
	if(pc && pc->GetPawn() && AbilitySystemComponent)
	{
		APawn* playerPawn = pc->GetPawn();
		AbilitySystemComponent->SetOwnerActor(playerPawn);
		WaitForPlayerPawnHandle.Invalidate();
	}
}

