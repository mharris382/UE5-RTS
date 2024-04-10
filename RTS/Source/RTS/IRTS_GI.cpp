#include "IRTS_GI.h"

// Sets default values
AIRTS_GI::AIRTS_GI()
{
	// Set this empty to call Tick() every frame. You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AIRTS_GI::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AIRTS_GI::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void AIRTS_GI::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}
