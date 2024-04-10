// Fill out your copyright notice in the Description page of Project Settings.


#include "RTS_PC.h"
#if PLATFORM_WINDOWS
#include "Windows/WindowsPlatformSplash.h"
#elif PLATFORM_PS4
#include "PS4/PS4Splash.h"
#elif PLATFORM_XBOXONE
#include "XboxOne/XboxOneSplash.h"
#elif PLATFORM_MAC
#include "Mac/MacPlatformSplash.h"
#elif PLATFORM_IOS
#include "IOS/IOSPlatformSplash.h"
#elif PLATFORM_ANDROID
#include "Android/AndroidSplash.h"
#elif PLATFORM_WINRT
#include "WinRT/WinRTSplash.h"
#elif PLATFORM_HTML5
#include "HTML5/HTML5PlatformSplash.h"
#elif PLATFORM_LINUX
#include "Linux/LinuxPlatformSplash.h"
#endif


void ARTS_PC::Tick(float DeltaTime)
{
	//TODO: check if using gamepad or mouse/keyboard
}

void ARTS_PC::BeginPlay()
{
#if PLATFORM_ANDROID || PLATFORM_IOS
	bIsMobile = true;
//#elif PLATFORM_PS4 || PLATFORM_PS5
//	bIsConsolePs = true;
//#elif PLATFORM_XBOXONE || PLATFORM_XBOXSERIES
//	bIsConsoleXbox = true;
#elif PLATFORM_SWITCH
	bIsConsoleSwitch = true;
#endif


	GetWorld()->GetTimerManager().SetTimerForNextTick(this, &ARTS_PC::InitDevices);
}

void ARTS_PC::InitDevices()
{
	if (bIsMobile) {
		SetActorTickEnabled(false);
		OnInputDeviceChanged.Broadcast(EInputDeviceType::Touch);
	}
	else
	{
		bool isConsole = bIsConsolePs || bIsConsoleXbox || bIsConsoleSwitch;
		SetActorTickEnabled(!isConsole);
		OnInputDeviceChanged.Broadcast(isConsole ? EInputDeviceType::Gamepad : EInputDeviceType::KeyMouse);
	}
}
