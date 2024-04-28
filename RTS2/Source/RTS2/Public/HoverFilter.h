// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "HoverFilter.generated.h"


UCLASS(Blueprintable, BlueprintType, ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class RTS2_API UHoverFilter : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UHoverFilter();

	UFUNCTION(BlueprintCallable, Category = "Selection")
	TArray<AActor*> FilterHoveredActors(const TArray<AActor*>& Actors);

	
	
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Selection")
	bool ShouldFilterActor(AActor* actor);

	bool ShouldFilterActor_Implementation(AActor* actor);
	
protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
};
