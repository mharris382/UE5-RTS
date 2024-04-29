// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Island.generated.h"

class UTextureRenderTarget2D;
class UMaterialInterface;

UCLASS()
class RTS2_API AIsland : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AIsland();

	// UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Island")
	// float IslandRadius = 10000;

	

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Island")
	TObjectPtr<AActor> IslandMeshActor;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Island")
	FVector IslandExtent;
	
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;


	UPROPERTY(EditDefaultsOnly, Category = "Island")
	float ExtraExtent = 0;
	
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable, Category = "Island")
	void SetIslandActor(AActor* actor);

	UFUNCTION(BlueprintCallable, Category = "Rendering")
	void GetUVBoundsOfActor(AActor* actor, FVector2D& uvMin, FVector2D& uvMax, float outlineDraw = 1.0f);

	UFUNCTION(BlueprintCallable, Category = "Rendering")
	bool GetUVPositionOfActor(AActor* actor, FVector2D& uvPosition);

	UFUNCTION(BlueprintCallable, Category = "Rendering")
	void DrawMaterialToTarget(UTextureRenderTarget2D* renderTarget, UMaterialInterface* material, FVector2D uvMin, FVector2D uvMax);

	UFUNCTION(BlueprintCallable, Category = "Rendering")
	void DrawActorToTarget(UTextureRenderTarget2D* renderTarget, UMaterialInterface* material, AActor* actor, float outlineDraw);
};
