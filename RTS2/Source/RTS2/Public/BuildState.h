// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "RTSPlayerState.h"
#include "BuildState.generated.h"


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class RTS2_API UBuildState : public URTSPlayerState
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UBuildState();

	UPROPERTY(EditDefaultsOnly, Category = "Input")
	TObjectPtr<UInputAction> RotateAction;

	UPROPERTY(EditDefaultsOnly, Category = "Input")
	TObjectPtr<UInputAction> BuildAction;
	
protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
	                           FActorComponentTickFunction* ThisTickFunction) override;

protected:
	virtual void BindStateActions(UEnhancedInputComponent* InputComponent) override;

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "State")
	void OnBuildPressed();

	virtual void OnBuildPressed_Implementation();
	virtual void OnCancelPressed_Implementation() override;
};
