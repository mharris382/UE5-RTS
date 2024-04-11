// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "IRTS_GI.h"
#include "UserSettings.h"
#include "Logging/LogMacros.h"
#include "RTS_GI.generated.h"
//DECLARE_LOG_CATEGORY_EXTERN(LogCoreGameInstance, Log, All);
/**
 * 
 */
UCLASS()
class RTS_API URTS_GI : public UGameInstance
{
	GENERATED_BODY()

public:
	virtual void Init() override;

	UFUNCTION(BlueprintCallable)
	FRandomStream GetRandomSeed() ;
	
	UFUNCTION(BlueprintCallable)
	TArray<FSaveInteract> GetSavedInteractables() ;
	
	UFUNCTION(BlueprintCallable)
	URTS_SaveGame* GetCurrentSaveData() ;
	
	UFUNCTION(BlueprintCallable)
	UUserSettings* GetUserSettings();

	UFUNCTION(BlueprintCallable)
	void StartNewGameInSaveSlot(int saveSlot);
	
	UFUNCTION(BlueprintCallable)
	bool LoadSaveSlot(int saveSlot) ;


	
	void BeginNewLevel() ;//replace with StartNewGameInSaveSlot
	
	UFUNCTION(BlueprintCallable)
	void SaveGame() ;
	
	UFUNCTION(BlueprintCallable)
	void UpdateSaveData() ;
	
	UFUNCTION(BlueprintCallable)
	void UpdateAllVillagers() ;
	
	UFUNCTION(BlueprintCallable)
	void UpdateAllWizards() ;
	
	UFUNCTION(BlueprintCallable)
	void UpdateAllStockpiles(TArray<FSaveStockpile> stockpiles) ;

	UFUNCTION(BlueprintCallable)
	float GetVolumeSetting(int index);
	
	UFUNCTION(BlueprintCallable)
	int GetQualitySetting(int index);

	UFUNCTION(BlueprintCallable)
	float SetVolumeSetting(int index, float volume);

	UFUNCTION(BlueprintCallable)
	int SetQualitySetting(int index, int quality);
	
	UFUNCTION(BlueprintCallable)
	bool HasSaveGameForSlot(int saveSlotIndex);

	UFUNCTION(BlueprintCallable)
	void ApplyUserSettings();

	UFUNCTION(BlueprintImplementableEvent, Category = "Action")
	void TestAction();

	TObjectPtr<UUserSettings> userSettings;
	TObjectPtr<URTS_SaveGame> currentSaveData;
	
	int currentSaveSlot;

	
	FString GetSaveSlot(int saveSlotIndex);
};
