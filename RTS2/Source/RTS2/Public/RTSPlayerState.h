// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "RTSPlayerState.generated.h"

class UInputAction;
class UEnhancedInputLocalPlayerSubsystem;
class UInputMappingContext;
struct FInputActionValue;

UCLASS(Blueprintable, BlueprintType, ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class RTS2_API URTSPlayerState : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	URTSPlayerState();

	UPROPERTY(EditDefaultsOnly, Category = "Input")
	TObjectPtr<UInputMappingContext> StateMappingContext;
	
	UPROPERTY(EditDefaultsOnly, Category = "Input")
	TObjectPtr<UInputAction> CancelAction;

	virtual void OnStateEnter();
	
	virtual void OnStateExit();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "State")
	void StateEnter();
	
	virtual void StateEnter_Implementation();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "State")
	void StateExit();
	
	virtual void StateExit_Implementation();
	
protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "State")
 	void OnCancelPressed();

	virtual void OnCancelPressed_Implementation();

	virtual void BindStateActions(UEnhancedInputComponent* InputComponent);
	
public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
	                           FActorComponentTickFunction* ThisTickFunction) override;

private:
	bool hasBoundActions = false;
};
