// Fill out your copyright notice in the Description page of Project Settings.


#include "RTS_BFL.h"

ARTS_GM* URTS_BFL::GetRTSGameMode(const UObject* WorldContextObject)
{
	if (!WorldContextObject) return nullptr;
	UWorld* world = GEngine->GetWorldFromContextObject(WorldContextObject, EGetWorldErrorMode::LogAndReturnNull);
	return world ? Cast<ARTS_GM>(world->GetAuthGameMode()) : nullptr;
}

URTS_GI* URTS_BFL::GetRTSGameInstance(const UObject* WorldContextObject)
{
	if (!WorldContextObject) return nullptr;
	UWorld* world = GEngine->GetWorldFromContextObject(WorldContextObject, EGetWorldErrorMode::LogAndReturnNull);
	return world ? Cast<URTS_GI>(world->GetGameInstance()) : nullptr;
}

ARTS_PlayerPawn* URTS_BFL::GetRTSPlayerPawn(const UObject* WorldContextObject)
{
	if (!WorldContextObject) return nullptr;
	UWorld* world = GEngine->GetWorldFromContextObject(WorldContextObject, EGetWorldErrorMode::LogAndReturnNull);
	if (!world)return nullptr;
	APlayerController* pc = world->GetFirstPlayerController();
	return pc ? Cast<ARTS_PlayerPawn>(pc->GetPawn()) : nullptr;
}

ARTS_PC* URTS_BFL::GetRTSPlayerController(const UObject* WorldContextObject)
{
	if (!WorldContextObject) return nullptr;
	UWorld* world = GEngine->GetWorldFromContextObject(WorldContextObject, EGetWorldErrorMode::LogAndReturnNull);
	if (!world)return nullptr;
	APlayerController* pc = world->GetFirstPlayerController();
	return pc ? Cast <ARTS_PC>(pc) : nullptr;
}
