// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "RTSPlayerController.generated.h"

class URTSPlayerState;
/**
 * 
 */
UCLASS()
class RTS2_API ARTSPlayerController : public APlayerController
{
	GENERATED_BODY()
public:
	
	ARTSPlayerController();

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "States")
	TSubclassOf<URTSPlayerState> DefaultPlayerStateClass;

	void ReturnToDefaultState();

	UFUNCTION(BlueprintCallable, Category = "States")
	void ChangeState(URTSPlayerState* newState);

	UFUNCTION(BlueprintCallable, Category = "States")
	void AddSubState(URTSPlayerState* newSubState);

	UFUNCTION(BlueprintCallable, Category = "States")
	void RemoveSubState(URTSPlayerState* newSubState);

protected:
	virtual void BeginPlay() override;
	virtual void OnPossess(APawn* aPawn) override;

private:

	UPROPERTY()
	TObjectPtr<URTSPlayerState> DefaultState;
	
	UPROPERTY()
	TObjectPtr<URTSPlayerState> CurrentState;

	UPROPERTY()
	TArray<TObjectPtr<URTSPlayerState>> SubStates;
};
