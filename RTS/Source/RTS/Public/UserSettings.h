// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "UserSettings.generated.h"

/**
 * 
 */
UCLASS()
class RTS_API UUserSettings : public USaveGame
{
	GENERATED_BODY()
public:

	UPROPERTY(VisibleAnywhere, Category = "SaveGame")
	FString mostRecentSaveSlot;

	UPROPERTY(VisibleAnywhere, Category = "SaveGame")
	TArray<int> qualitySettings;

	UPROPERTY(VisibleAnywhere, Category = "SaveGame")
	TArray<float> soundMixes;
	
};
