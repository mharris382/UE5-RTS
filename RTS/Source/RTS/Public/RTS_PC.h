// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "RTS_PC.generated.h"


UENUM(BlueprintType)
enum class EInputDeviceType : uint8
{
	Unknown,
	KeyMouse,
	Gamepad,
	Touch
};
/**
 * 
 */
UCLASS()
class RTS_API ARTS_PC : public APlayerController
{
	GENERATED_BODY()
	
public:
	// Delegate declaration
	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FEventInputChanged, EInputDeviceType, deviceType);

	UPROPERTY(BlueprintAssignable)
	FEventInputChanged OnInputDeviceChanged;

	virtual void Tick(float DeltaTime) override;
	virtual void BeginPlay() override;
private:
	bool bIsMobile = false;
	bool bIsConsolePs = false;
	bool bIsConsoleXbox = false;
	bool bIsConsoleSwitch = false;

	void InitDevices();
};
