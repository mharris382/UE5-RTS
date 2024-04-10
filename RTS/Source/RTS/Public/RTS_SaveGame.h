// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "UObject/RandomStream.h"
#include "GameFramework/SaveGame.h"
#include "RTS_SaveGame.generated.h"

UENUM(BlueprintType)
enum class EResourceType : uint8
{
    Stone,
    Wood,
    Food,
    Crystal
};

USTRUCT(BlueprintType)
struct FStockpile
{
    GENERATED_BODY()
    
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SaveGame")
    TArray<EResourceType> allowedTypes;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SaveGame")
    TMap<EResourceType, int32> Resources;
};

USTRUCT(BlueprintType)
struct FSaveInteract
{
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SaveGame")
    FTransform Location;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Save Game")
    TSubclassOf<AActor> Type;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SaveGame")
    float Health;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SaveGame")
    FName Tag;
}

USTRUCT(BlueprintType)
struct FSaveAgent
{
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SaveGame")
    FVector Location;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SaveGame")
    FName Task;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SaveGame")
    float Health;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SaveGame")
    FText Name;
}


USTRUCT(BlueprintType)
struct FSaveVillager
{
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SaveGame")
    FSaveAgent basicInfo;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SaveGame")
    float EnergyLevel;
};

USTRUCT(BlueprintType)
struct FSaveWizard
{
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SaveGame")
    FSaveAgent basicInfo;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SaveGame")
    float Mana;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SaveGame")
    TArray<FName> unlockedSpells;
};

/**
 * 
 */
UCLASS()
class RTS_API URTS_SaveGame : public USaveGame
{
	GENERATED_BODY()
	
public:

    UPROPERTY(VisibleAnywhere, Category = "SaveGame")
    FRandomStream Seed;

    UPROPERTY(VisibleAnywhere, Category = "SaveGame")
    TArray<FStockpile> Stockpiles;

    UPROPERTY(VisibleAnywhere, Category = "SaveGame")
    TArray<FSaveInteract> Interactables;

    UPROPERTY(VisibleAnywhere, Category = "SaveGame")
    int archwizardIndex;

    UPROPERTY(VisibleAnywhere, Category = "SaveGame")
    TArray<FSaveWizard> Wizards;

    UPROPERTY(VisibleAnywhere, Category = "SaveGame")
    TArray<FSaveVillager> Villagers;

    
    
};
