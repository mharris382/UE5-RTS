// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "PlayerPawnStateComponent.generated.h"

class UInputAction;
class UInputMappingContext;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class UPlayerPawnStateComponent : public UActorComponent
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UInputMappingContext> StateMappingContext;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UInputAction> CancelAction;

public:	
	// Sets default values for this component's properties
	UPlayerPawnStateComponent();

	 UFUNCTION(BlueprintImplementableEvent)
	 void OnStateEntered(UEnhancedInputLocalPlayerSubsystem* inputSubsystem);

	 UFUNCTION(BlueprintImplementableEvent)
	 void OnStateExited(UEnhancedInputLocalPlayerSubsystem* inputSubsystem);

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	virtual void EnterState();

	virtual void ExitState();
		
};
