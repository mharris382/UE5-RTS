// Fill out your copyright notice in the Description page of Project Settings.


#include "Agent.h"

#include "AbilitySystemComponent.h"
#include "WizardAttributeSet.h"
#include "Components/SkeletalMeshComponent.h"
#include "GameFramework/FloatingPawnMovement.h"
#include "Components/CapsuleComponent.h"
#include "UObject/ConstructorHelpers.h"
#include "Kismet/KismetMathLibrary.h"

// Sets default values
AAgent::AAgent()
{
	
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Collision = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Capsule"));
	RootComponent = Collision;

	// SkeletalMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("SkeletalMesh"));
	// SkeletalMesh->SetupAttachment(Collision);
	// static ConstructorHelpers::FObjectFinder<USkeletalMesh> mesh(TEXT("/Script/Engine.SkeletalMesh'/Game/Characters/Meshes/SKM_Villager.SKM_Villager'"));
	// if(mesh.Succeeded())
	// {
	// 	SkeletalMesh->SetSkeletalMesh(mesh.Object);
	// 	SkeletalMesh->SetCustomPrimitiveDataFloat(0,UKismetMathLibrary::RandomFloat());
	// 	SkeletalMesh->SetCustomPrimitiveDataFloat(1,UKismetMathLibrary::RandomFloat());
	// }
	//
	// Hat = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Hat"));
	// Hat->SetupAttachment(SkeletalMesh, TEXT("headSocket"));
	//
	// Hair = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Hair"));
	// Hair->SetupAttachment(SkeletalMesh);
	
	Movement = CreateDefaultSubobject<UFloatingPawnMovement>(TEXT("FloatingPawnMovement"));
}

// Called when the game starts or when spawned
void AAgent::BeginPlay()
{
	Super::BeginPlay();
	
}

UFloatingPawnMovement* AAgent::GetMovement() const
{
	return  Movement;
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





