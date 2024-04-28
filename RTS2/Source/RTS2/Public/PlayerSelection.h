// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "PlayerSelection.generated.h"


UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FFocusedActorChanged, AActor*, FocusedActor);

UCLASS(Blueprintable, BlueprintType ,ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class RTS2_API UPlayerSelection : public UActorComponent
{
	GENERATED_BODY()

	
public:	
	// Sets default values for this component's properties
	UPlayerSelection();

	FFocusedActorChanged OnFocusedActorChanged;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Selection")
	TObjectPtr<AActor> FocusedActor;

	UFUNCTION(BlueprintCallable, Category = "Selection")
	bool SetFocusedActor(AActor* selectedActor);

	UFUNCTION(BlueprintCallable, Category = "Selection")
	void ClearFocusedActor();

	UFUNCTION(BlueprintCallable, Category = "Selection")
	void OnPawnDragged(APawn* draggedPawn, FVector dragEndPosition, AActor* dragEndActor, TArray<FVector> pathPoints);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Selection")
	void FocusedActorChanged(AActor* actor);

	void FocusedActorChanged_Implementation(AActor* actor);
	
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Selection")
	void OnPawnDraggedToActor(APawn* draggedPawn,AActor* draggedOntoActor);

	void OnPawnDraggedToActor_Implementation(APawn* draggedPawn,AActor* draggedOntoActor);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Selection")
	void OnPawnDraggedToLocation(APawn* draggedPawn,FVector dragEndPosition);

	virtual void OnPawnDraggedToLocation_Implementation(APawn* draggedPawn,FVector dragEndPosition);
protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
};
