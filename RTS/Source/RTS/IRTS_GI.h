#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "IRTS_GI.generated.h"

UCLASS()
class RTS_API AIRTS_GI : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this empty's properties
	AIRTS_GI();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
};
