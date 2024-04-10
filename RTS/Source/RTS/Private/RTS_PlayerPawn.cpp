// Fill out your copyright notice in the Description page of Project Settings.


#include "RTS_PlayerPawn.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Components/SphereComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Engine/Engine.h"
#include "GameFramework/Controller.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Kismet/KismetMathLibrary.h"
#include "InputActionValue.h"


namespace
{
	FTimerHandle MoveTimerHandle;
}

// Sets default values
ARTS_PlayerPawn::ARTS_PlayerPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	DefaultSceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("DefaultSceneRoot"));
	RootComponent = DefaultSceneRoot;

	Collision = CreateDefaultSubobject<USphereComponent>(TEXT("Collision"));
	Collision->SetSphereRadius(180.0);
	Collision->SetupAttachment(DefaultSceneRoot);

	Cursor = CreateDefaultSubobject <UStaticMeshComponent>(TEXT("Cursor"));
	Cursor->SetupAttachment(DefaultSceneRoot);

	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(DefaultSceneRoot);

	Movement = CreateDefaultSubobject<UFloatingPawnMovement>(TEXT("FloatingPawnMovement"));
	Movement->MaxSpeed = 1500.0;
	Movement->Acceleration = 8000.0;
	Movement->Deceleration = 6500.0;
	Movement->TurningBoost = 8.0;
	Movement->bConstrainToPlane = true;
	Movement->bSnapToPlaneAtStart = true;
	Movement->SetPlaneConstraintAxisSetting(EPlaneConstraintAxisSetting::Custom);
		
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	
	
}

// Called when the game starts or when spawned
void ARTS_PlayerPawn::BeginPlay()
{
	Super::BeginPlay();
	
	
	
	//add base input context which contains movement and camera controls
	if (APlayerController* PC = Cast<APlayerController>(Controller))
	{
		//listen for input device changes (or just set input device mode)
		ARTS_PC* rtsPC = Cast<ARTS_PC>(PC);
		if (rtsPC) 
		{
			rtsPC->OnInputDeviceChanged.AddDynamic(this, &ARTS_PlayerPawn::SwitchInputDeviceType);
		}

		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem< UEnhancedInputLocalPlayerSubsystem>(PC->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(BaseInputMappingContext, 0);
		}
	}

	SwitchInputDeviceType(EInputDeviceType::KeyMouse);
	UpdateZoom();
	GetWorld()->GetTimerManager().SetTimer(MoveTimerHandle, this, &ARTS_PlayerPawn::MoveTracking, 0.016667, true);

}

void ARTS_PlayerPawn::Move(const FInputActionValue& Value)
{
	
	AddMovementInput(GetActorForwardVector(), Value.Get<FInputActionValue::Axis2D>().Y, false);
	AddMovementInput(GetActorRightVector(), Value.Get<FInputActionValue::Axis2D>().X, false);
}

void ARTS_PlayerPawn::Zoom(const FInputActionValue& Value)
{
	ZoomDirection = Value.Get<float>();
	UpdateZoom();
	Dof();
}

void ARTS_PlayerPawn::Spin(const FInputActionValue& Value)
{
	
	AddActorLocalRotation(FRotator(0.0, Value.Get<FInputActionValue::Axis1D>(), 0.0));
}

void ARTS_PlayerPawn::MoveTracking()
{
	FString msg = FString::Printf(TEXT("Move Tracking Called"));
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, msg);

	FVector locationNormalized = GetActorLocation();
	locationNormalized.Normalize();
	AddMovementInput(FVector(locationNormalized.X, locationNormalized.Y, 0) * -1, FMath::Max((GetActorLocation().Length() - 9000) / 5000, 0));
	UpdateCursorPosition();

	APlayerController* PC = Cast<APlayerController>(Controller);


	//Move at Edge of Screen
	
	if (PC) {
		FVector2D screenPosition;
		FVector Intersection;
		if (ProjectMouseOrTouchToGroundPlane(screenPosition, Intersection))
		{
			int32 vpSizeX;
			int32 vpSizeY;
			PC->GetViewportSize(vpSizeX, vpSizeY);

			FVector2D screenCenter = FVector2D(vpSizeX / 2.0, vpSizeY / 2.0);
			FVector2D screenOffset = screenPosition - screenCenter;
			float dMove = EdgeMoveDistance * (inputDeviceType == EInputDeviceType::KeyMouse) ? 2 : 1;
			float centerX = (float)vpSizeX / 2.0;
			float centerY = (float)vpSizeY / 2.0;
			float moveX = FMath::Sign(screenOffset.X) * (FMath::Max(0, FMath::Abs(screenOffset.X) - (centerX - dMove)) / EdgeMoveDistance);
			float moveY = FMath::Sign(screenOffset.Y) * (FMath::Max(0, FMath::Abs(screenOffset.Y) - (centerY - dMove)) / EdgeMoveDistance) * -1;
			FVector moveDirection = FVector(moveX, moveY, 0);
			FTransform t = GetActorTransform();
			FVector direction = UKismetMathLibrary::TransformDirection(t, moveDirection);
			AddMovementInput(direction, 1);
			if (ProjectMouseOrTouchToGroundPlane(screenPosition, Intersection))
			{
				Collision->SetWorldLocation(Intersection + FVector(0, 0, 10));
			}
		}
		else {
			msg = FString::Printf(TEXT("No Ground Intersection Found"));
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, msg);
		}
	}

	//---------------------
	
}

void ARTS_PlayerPawn::DragMove(const FInputActionValue& Value)
{
	APlayerController* PC = Cast<APlayerController>(Controller);
	bool twoTouch = false;
	if (PC)
	{
		float locationX;
		float locationY;
		bool isCurrentlyPressedTwoFinger;
		PC->GetInputTouchState(ETouchIndex::Touch2, locationX, locationY, isCurrentlyPressedTwoFinger);
		if (isCurrentlyPressedTwoFinger)
		{
			if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem< UEnhancedInputLocalPlayerSubsystem>(PC->GetLocalPlayer()))
			{
				FModifyContextOptions opts = FModifyContextOptions();
				opts.bIgnoreAllPressedKeysUntilRelease = true;
				opts.bForceImmediately = true;
				opts.bNotifyUserSettings = false;

				Subsystem->RemoveMappingContext(DragMoveMappingContext, opts);
			}
		}
		else {
			TrackMove();
		}
	}
}

void ARTS_PlayerPawn::TrackMove()
{
	FVector2D screenPosition;
	FVector Intersection;
	if (ProjectMouseOrTouchToGroundPlane(screenPosition, Intersection))
	{
		FVector vertOffset = CameraBoom->GetUpVector() * CameraBoom->SocketOffset.Z;
		FVector backOffset = (CameraBoom->TargetArmLength - CameraBoom->SocketOffset.X) * CameraBoom->GetForwardVector() * -1;
		FVector worldLoc = CameraBoom->GetComponentLocation();
		FVector camWorldLoc = FollowCamera->GetComponentLocation();
		FVector offsetBetweenCameraAndSpringArm = ((vertOffset + backOffset + worldLoc) - camWorldLoc);

		StoredMove = HandleTarget - Intersection - offsetBetweenCameraAndSpringArm;
		AddActorWorldOffset(FVector(StoredMove.X, StoredMove.Y, 0));
	}
}

void ARTS_PlayerPawn::PositionCheck()
{
	FVector2D screenPosition;
	FVector Intersection;
	if (ProjectMouseOrTouchToGroundPlane(screenPosition, Intersection))
	{
		HandleTarget = Intersection;
		if (inputDeviceType == EInputDeviceType::Touch)
		{
			Collision->SetWorldLocation(Intersection);
		}
	}
}

bool ARTS_PlayerPawn::ProjectMouseOrTouchToGroundPlane(FVector2D& ScreenPosition, FVector& Intersection)
{
	APlayerController* PC = Cast<APlayerController>(Controller);
	if (PC)
	{
		int32 vpSizeX;
		int32 vpSizeY;
		PC->GetViewportSize(vpSizeX, vpSizeY);
		FVector2D screenCenter = FVector2D(vpSizeX / 2.0, vpSizeY / 2.0);

		float touchLocationX;
		float touchLocationY;
		bool isTouchCurrentlyPressed;
		
		PC->GetInputTouchState(ETouchIndex::Touch1, touchLocationX, touchLocationY, isTouchCurrentlyPressed);
		FVector2D touchLocation = FVector2D(touchLocationX, touchLocationY);
		if (isTouchCurrentlyPressed) {
			SwitchInputDeviceType(EInputDeviceType::Touch);
		}

		float mouseLocationX;
		float mouseLocationY;
		bool isMouseCurrentlyPressed = PC->GetMousePosition(mouseLocationX, mouseLocationY);
		FVector2D mouseLocation = FVector2D(mouseLocationX, mouseLocationY);
		if (isMouseCurrentlyPressed) {
			SwitchInputDeviceType(EInputDeviceType::KeyMouse);
		}

		FVector2D targetLocation;
		switch (inputDeviceType)
		{
		case EInputDeviceType::Touch:
			targetLocation = touchLocation;
			break;
		case EInputDeviceType::Gamepad:
		case EInputDeviceType::Unknown:
			targetLocation = screenCenter;
			break;
		case EInputDeviceType::KeyMouse:
			targetLocation = mouseLocation;
			break;
		default:
			break;
		}

		ScreenPosition = targetLocation;
		FVector worldPosition;
		FVector worldDirection;
		PC->DeprojectScreenPositionToWorld(ScreenPosition.X, ScreenPosition.Y, worldPosition, worldDirection);
		FPlane groundPlane = FPlane(FVector(0, 0, 0), FVector(0, 0, 1));
		
		FVector intersection;
		float t;
		bool intersected = UKismetMathLibrary::LinePlaneIntersection(worldPosition, worldPosition + (worldDirection * 10000000), groundPlane, t, intersection);

		FVector offset = FVector(0, 0, (inputDeviceType == EInputDeviceType::Touch && isTouchCurrentlyPressed) ? -500 : 0);
		Intersection = intersection + offset;
		return inputDeviceType != EInputDeviceType::Unknown;
	}
	return false;
}

void ARTS_PlayerPawn::SwitchInputDeviceType(EInputDeviceType type)
{
	inputDeviceType = type;
	switch (inputDeviceType)
	{
	case EInputDeviceType::Touch:
		Cursor->SetHiddenInGame(true, true);
		Collision->SetRelativeLocation(FVector(0, 0, -500));
		break;
	case EInputDeviceType::Gamepad:
		Collision->SetRelativeLocation(FVector(0, 0, 0));
		break;

	case EInputDeviceType::KeyMouse:
		Cursor->SetHiddenInGame(false, true);
		break;

	default:
		break;
	}
}

void ARTS_PlayerPawn::UpdateCursorPosition()
{
	if (inputDeviceType == EInputDeviceType::Touch)
	{
		return;
	}
	FTransform target;
	if (HoverActor != NULL)
	{
		FVector origin;
		FVector boxExtents;
		HoverActor->GetActorBounds(true, origin, boxExtents, false);
		float cursorAnimationScale =  (FVector2D(boxExtents.X, boxExtents.Y).GetAbsMax() / 50) + (FMath::Sin(5 * GetWorld()->TimeSeconds) * 25) + 1;
		target = FTransform(FRotator(0, 0, 0), FVector(origin.X, origin.Y, 0), FVector(cursorAnimationScale, cursorAnimationScale, 0));
	}
	else
	{
		FTransform colTransform = Collision->GetComponentTransform();
		target = FTransform(colTransform.GetRotation(), colTransform.GetLocation(), FVector(2, 2, 1));
	}
	Cursor->SetWorldTransform(target);
}

void ARTS_PlayerPawn::UpdateZoom()
{
	ZoomValue = UKismetMathLibrary::Clamp((ZoomDirection * 0.1) + ZoomValue, 0, 1);
	float t = ZoomCurve->GetFloatValue(ZoomValue);
	CameraBoom->TargetArmLength = UKismetMathLibrary::Lerp(800, 40000, t);
	CameraBoom->SetRelativeRotation(FRotator(UKismetMathLibrary::Lerp(-40, -55, t), 0, 0));
	Movement->MaxSpeed = UKismetMathLibrary::Lerp(1000, 6000, t);
	Dof();
	FollowCamera->SetFieldOfView(UKismetMathLibrary::Lerp(20, 15, t));
}

void ARTS_PlayerPawn::Dof()
{
	FPostProcessSettings pps = FPostProcessSettings();
	pps.DepthOfFieldFstop = 3;
	pps.DepthOfFieldSensorWidth = 150.0;
	pps.DepthOfFieldFocalDistance = CameraBoom->TargetArmLength;
}




// Called every frame
void ARTS_PlayerPawn::Tick(float DeltaTime)
{
	

}

// Called to bind functionality to input
void ARTS_PlayerPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	if (UEnhancedInputComponent* InputComp = Cast<UEnhancedInputComponent>(PlayerInputComponent)) {

		InputComp->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ARTS_PlayerPawn::Move);
		InputComp->BindAction(ZoomAction, ETriggerEvent::Triggered, this, &ARTS_PlayerPawn::Zoom);
		InputComp->BindAction(SpinAction, ETriggerEvent::Triggered, this, &ARTS_PlayerPawn::Spin);
		InputComp->BindAction(DragMoveAction, ETriggerEvent::Triggered, this, &ARTS_PlayerPawn::DragMove);
	}
}

