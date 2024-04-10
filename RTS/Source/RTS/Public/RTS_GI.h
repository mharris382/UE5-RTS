// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "UserSettings.h"
#include "RTS_GI.generated.h"

/**
 * 
 */
UCLASS()
class RTS_API URTS_GI : public UGameInstance
{
	GENERATED_BODY()
public:


protected:

	TObjectPtr<UUserSettings> userSettings;
};
