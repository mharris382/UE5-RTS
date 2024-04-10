// Fill out your copyright notice in the Description page of Project Settings.


#include "Agent.h"



// Sets default values
AAgent::AAgent()
{
	Capsule = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Capsule"));
	RootComponent = Capsule;
	Capsule->SetCapsuleRadius(30.0);
	Capsule->SetCapsuleHalfHeight(92.03);

	SkeletalMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("SkeletalMesh"));
	SkeletalMesh->SetupAttachment(Capsule);


	PawnMovement = CreateDefaultSubobject<UFloatingPawnMovement>(TEXT("FloatingPawnMovement"));
	if (PawnMovement) 
	{
		PawnMovement->UpdatedComponent = Capsule;
	}
	PawnMovement->MaxSpeed = MaxSpeed;
	PawnMovement->Acceleration = Acceleration;
	PawnMovement->Deceleration = Acceleration * 2;
	PawnMovement->TurningBoost = 8;
	PawnMovement->bConstrainToPlane = false;
	
	HighlightedCursor = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("HighlightedCursor"));
	HighlightedCursor->SetupAttachment(Capsule);

 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AAgent::BeginPlay()
{
	Super::BeginPlay();
	AddActorWorldOffset(FVector(0.0, 0.0, Capsule->GetScaledCapsuleHalfHeight()));

}

// Called every frame
void AAgent::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void AAgent::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}
