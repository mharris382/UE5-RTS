// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Logging/LogMacros.h"
#include "GameFramework/FloatingPawnMovement.h"
#include "Curves/CurveFloat.h"
#include "Logging/LogMacros.h"
#include "GameFramework/Actor.h"
#include "RTS_PC.h"
#include "RTS_PlayerPawn.generated.h"

UENUM(BlueprintType)
enum class EPlayerInputMode : uint8
{
	Villager,
	Build,
	Destruct
};



class UCurveFloat;
class USceneComponent;
class UInputComponent;
class USphereComponent;
class UCameraComponent;
class UInputAction;
class UInputMappingContext;
class USpringArmComponent;
struct FInputActionValue;

UCLASS()
class RTS_API ARTS_PlayerPawn : public APawn
{
	GENERATED_BODY()

	

	/*UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputMappingContext* VillagerMappingContext;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputMappingContext* BuildMappingContext;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputMappingContext* DestructMappingContext;*/

	//UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	//UInputAction* CancelAction;

	//UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	//UInputAction* DestructConfirmAction;

	//UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	//UInputAction* DestructQueueAction;

	

public:
	// Sets default values for this pawn's properties
	ARTS_PlayerPawn();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	TObjectPtr<USceneComponent> DefaultSceneRoot;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	TObjectPtr< USphereComponent> Collision;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UStaticMeshComponent> Cursor;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	TObjectPtr < USpringArmComponent> CameraBoom;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UCameraComponent> FollowCamera;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UFloatingPawnMovement> Movement;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	TObjectPtr < UInputAction> MoveAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	TObjectPtr < UInputAction>  ZoomAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	TObjectPtr <UCurveFloat> ZoomCurve;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	TObjectPtr < UInputAction>  SpinAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	TObjectPtr < UInputAction>  DragMoveAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	TObjectPtr < UInputMappingContext> BaseInputMappingContext;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	TObjectPtr < UInputMappingContext> DragMoveMappingContext;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Default", meta = (AllowPrivateAccess = "true"))
	FVector HandleTarget;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Default", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<AActor> HoverActor;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Default", meta = (AllowPrivateAccess = "true"))
	float EdgeMoveDistance = 50;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void Move(const FInputActionValue& Value);

	void Zoom(const FInputActionValue& Value);

	void Spin(const FInputActionValue& Value);

	void MoveTracking();

	void DragMove(const FInputActionValue& Value);


	void TrackMove();

	void PositionCheck();

	bool ProjectMouseOrTouchToGroundPlane(FVector2D& ScreenPosition, FVector& Intersection);

	void SwitchInputDeviceType(EInputDeviceType type);

	void UpdateCursorPosition();

	void UpdateZoom();
	void Dof();

	float ZoomDirection;
	float ZoomValue = 0.5;

	EInputDeviceType inputDeviceType;

	FVector StoredMove;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	/** Returns FollowCamera subobject **/
	FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera; }
};
