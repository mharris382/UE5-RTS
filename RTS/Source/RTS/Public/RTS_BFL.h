// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "Engine/Engine.h"
#include "GameFramework/GameModeBase.h"
#include "GameFramework/PlayerController.h"
#include "GameFramework/Pawn.h"
#include "Engine/GameInstance.h"
#include "RTS_GI.h"
#include "RTS_GM.h"
#include "RTS_PC.h"
#include "RTS_PlayerPawn.h"
#include "RTS_BFL.generated.h"

/**
 * 
 */
UCLASS()
class RTS_API URTS_BFL : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintCallable, Category = "Game", meta = (WorldContext = "WorldContextObject"))
	static ARTS_GM* GetRTSGameMode(const UObject* WorldContextObject);

	UFUNCTION(BlueprintCallable, Category = "Game", meta = (WorldContext = "WorldContextObject"))
	static URTS_GI* GetRTSGameInstance(const UObject* WorldContextObject);

	UFUNCTION(BlueprintCallable, Category = "Game", meta = (WorldContext = "WorldContextObject"))
	static ARTS_PlayerPawn* GetRTSPlayerPawn(const UObject* WorldContextObject);

	UFUNCTION(BlueprintCallable, Category = "Game", meta = (WorldContext = "WorldContextObject"))
	static ARTS_PC* GetRTSPlayerController(const UObject* WorldContextObject);
};
