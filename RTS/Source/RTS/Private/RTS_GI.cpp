// Fill out your copyright notice in the Description page of Project Settings.

#include "RTS_GI.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/Engine.h"
#include "GameFramework/GameUserSettings.h"

void URTS_GI::Init()
{
	if (!userSettings)
	{
		if (UGameplayStatics::DoesSaveGameExist(FString("SETTINGS"), 0))
		{
			userSettings = Cast<UUserSettings>(UGameplayStatics::LoadGameFromSlot(FString("SETTINGS"), 0));
			currentSaveSlot = userSettings->mostRecentSaveSlot;
		}
		else {
			currentSaveSlot = -1;
			userSettings = Cast<UUserSettings>(UGameplayStatics::CreateSaveGameObject(UUserSettings::StaticClass()));
			//need to create a TArray<float> with 2 values intialized to 1 (max value)
			userSettings->soundMixes.Init(1.0f, 2);
		}
	}
}

FRandomStream URTS_GI::GetRandomSeed()
{
	if(!currentSaveData) return currentSaveData->Seed;
	return 0;
}

TArray<FSaveInteract> URTS_GI::GetSavedInteractables()
{
	if(!currentSaveData) return currentSaveData->Interactables;
	return TArray<FSaveInteract>();
}

URTS_SaveGame* URTS_GI::GetCurrentSaveData()
{
	if(!currentSaveData) return nullptr;
	return currentSaveData;
}

UUserSettings* URTS_GI::GetUserSettings()
{
	if (!userSettings)
	{
		if (!UGameplayStatics::DoesSaveGameExist(FString("SETTINGS"), 0))
		{
			userSettings = Cast<UUserSettings>(UGameplayStatics::LoadGameFromSlot(FString("SETTINGS"), 0));
			currentSaveSlot = userSettings->mostRecentSaveSlot;
		}
		else {
			currentSaveSlot = -1;
			userSettings = Cast<UUserSettings>(UGameplayStatics::CreateSaveGameObject(UUserSettings::StaticClass()));
			//need to create a TArray<float> with 2 values intialized to 1 (max value)
			userSettings->soundMixes.Init(1.0f, 2);
			//TODO: add all quality settings
			userSettings->qualitySettings.Init(3, 2);
		}
	}
	return userSettings;
}

void URTS_GI::StartNewGameInSaveSlot(int saveSlot)
{
	currentSaveSlot = saveSlot;
	currentSaveData = Cast<URTS_SaveGame>(UGameplayStatics::CreateSaveGameObject(URTS_SaveGame::StaticClass()));
}

bool URTS_GI::LoadSaveSlot(int saveSlot)
{
	if(saveSlot <= 0)
		return false;
	FString saveSlotName = GetSaveSlot(saveSlot);
	if(!UGameplayStatics::DoesSaveGameExist(saveSlotName, 0))
	{
		return false;
	}
	
	currentSaveSlot = saveSlot;
	currentSaveData = Cast<URTS_SaveGame>(UGameplayStatics::LoadGameFromSlot(saveSlotName, 0));
	
	return true;
}

void URTS_GI::BeginNewLevel()
{
	//TODO: implement new level
}

void URTS_GI::SaveGame()
{
	if(!currentSaveData)
	{
		//UE_LOG(LogCoreGameInstance, Warning, TEXT("No Save File Exists in Game Instance"));
		return;
	}
	currentSaveSlot = currentSaveSlot > 0 ? currentSaveSlot : 1;
	FString saveSlot = GetSaveSlot(currentSaveSlot);
	bool success = UGameplayStatics::SaveGameToSlot(currentSaveData, saveSlot, 0);
	if(success)
	{
		//UE_LOG(LogCoreGameInstance, Log, TEXT("Save Filed to save :SAVE_%d"), currentSaveSlot);
		if(userSettings && userSettings->mostRecentSaveSlot!=currentSaveSlot)
		{
			userSettings->mostRecentSaveSlot = currentSaveSlot;
			UGameplayStatics::SaveGameToSlot(userSettings, TEXT("SETTINGS"), 0);
		}
	}
	else
	{
		//UE_LOG(LogCoreGameInstance, Error, TEXT("FAILED to to save game to slot :SAVE_%d"), currentSaveSlot);
	}
	
	return;
}

void URTS_GI::UpdateSaveData()
{
	if(!currentSaveData)
	{
		//UE_LOG(LogCoreGameInstance, Warning, TEXT("No Save File Exists in Game Instance"));
		return;
	}
	UpdateAllVillagers();
	UpdateAllWizards();
	//TODO: implement update all save data
	return;
}

void URTS_GI::UpdateAllVillagers()
{
	if(!currentSaveData)
	{
		//UE_LOG(LogCoreGameInstance, Warning, TEXT("No Save File Exists in Game Instance"));
		return;
	}
	//TODO: implement update villagers save data
	return;
}

void URTS_GI::UpdateAllWizards()
{
	if(!currentSaveData)
	{//
		//UE_LOG(LogCoreGameInstance, Warning, TEXT("No Save File Exists in Game Instance"));
		return;
	}
	//TODO: implement update villagers save data
	
}

void URTS_GI::UpdateAllStockpiles(TArray<FSaveStockpile> stockpiles)
{
	if(!currentSaveData)
	{
		///UE_LOG(LogCoreGameInstance, Warning, TEXT("No Save File Exists in Game Instance"));
		return;
	}
	currentSaveData->Stockpiles.Empty();
	for (const FSaveStockpile& sp : stockpiles) {
		currentSaveData->Stockpiles.Add(sp);
	}
}

float URTS_GI::GetVolumeSetting(int index)
{
	UUserSettings* settings = GetUserSettings();
	return settings->soundMixes[index];
}

int URTS_GI::GetQualitySetting(int index)
{
	UUserSettings* settings = GetUserSettings();
	
	return settings->qualitySettings[index];
}

float URTS_GI::SetVolumeSetting(int index, float volume)
{
	UUserSettings* settings = GetUserSettings();
	settings->soundMixes[index] = volume;
	return volume;
}

int URTS_GI::SetQualitySetting(int index, int quality)
{
	UUserSettings* settings = GetUserSettings();
	settings->qualitySettings[index] = quality;
	return quality;
}

bool URTS_GI::HasSaveGameForSlot(int saveSlotIndex)
{
	return UGameplayStatics::DoesSaveGameExist(GetSaveSlot(saveSlotIndex), 0);
}

void URTS_GI::ApplyUserSettings()
{
	UUserSettings* settings = GetUserSettings();
	UGameUserSettings* gameUserSettings = UGameUserSettings::GetGameUserSettings();
	gameUserSettings->SetShadowQuality(settings->qualitySettings[0]);
	gameUserSettings->SetVisualEffectQuality(settings->qualitySettings[1]);
}

//void URTS_GI::TestAction()
//{
//	GEngine->AddOnScreenDebugMessage(0, 1, FColor::Blue, TEXT("TEST ACTION"));
//}

FString URTS_GI::GetSaveSlot(int saveSlotIndex)
{
	return FString::Printf(TEXT("SAVE_%d"), saveSlotIndex);
}
