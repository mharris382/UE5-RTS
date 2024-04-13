// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"

UENUM(BlueprintType)
enum class EAbilityInputID : uint8
{
    None,
    Confirm,
    Cancel,
    Punch,
    Cast
};

UENUM(BlueprintType)
enum class EWizardDiscipline : uint8
{
    Novice,
    Arcane,
    Elemental,
    Druid,
    Holy,
    Demonic
};