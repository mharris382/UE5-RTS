// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Engine/TextureRenderTarget2D.h"
#include "Engine/DataTable.h"
#include "Interactable.generated.h"

class USceneComponent;
class UDecalComponent;
class UBoxComponent;


UCLASS()
class RTS_API AInteractable : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AInteractable();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	TObjectPtr<USceneComponent> Scene;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	TObjectPtr<UStaticMeshComponent> BaseMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	TObjectPtr< UBoxComponent> Box;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	TObjectPtr<UDecalComponent> Decal;



	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ground Blend")
	bool EnabledGroundBlend = true;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ground Blend")
	float OutlineDraw = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ground Blend")
	TObjectPtr<UTextureRenderTarget2D> RenderTextureTarget;



	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Progression")
	bool RequiresBuild = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Progression")
	float ProgressionState = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Progression")
	TArray< TObjectPtr<UStaticMesh>> MeshList;

	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawn Info")
	FVector BoundScale = FVector(1, 1, 1);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawn Info")
	FDataTableRowHandle SpawnKey;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;


	UFUNCTION(BlueprintCallable)
	void SetProgressionState(float progress);

	UFUNCTION(BlueprintCallable)
	void PlacementMode();

	UFUNCTION(BlueprintCallable)
	void TransformToTexture(FVector2D inVec, FVector2D& vec1, FVector2D& vec2);

private:

	float BoundGap;

	void UpdateBoxBounds();

	void VerifyReferencesSet();

public:
	virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;
	virtual void PostLoad() override;
};
