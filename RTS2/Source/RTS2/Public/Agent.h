// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Agent.generated.h"

class USkeletalMeshComponent;
class UFloatingPawnMovement;
class UCapsuleComponent;

UCLASS(config=Game)
class RTS2_API AAgent : public APawn
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	UCapsuleComponent* Collision;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	UFloatingPawnMovement* Movement;
	// UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	// USkeletalMeshComponent* SkeletalMesh;
	//
	// UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	// USkeletalMeshComponent* Hat;
	//
	// UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	// USkeletalMeshComponent* Hair;

	

public:
	// Sets default values for this pawn's properties
	AAgent();
	
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFloatingPawnMovement* GetMovement() const;
	
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual class UAbilitySystemComponent* GetAgentAbilitySystemComponent() const { return nullptr; }

	

private:

	
	
	
};
