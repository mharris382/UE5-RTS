// Fill out your copyright notice in the Description page of Project Settings.


#include "Environment/Island.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/KismetRenderingLibrary.h"
#include "Engine/TextureRenderTarget2D.h"
#include "Materials/MaterialInterface.h"
#include "Engine/Canvas.h"
// Sets default values
AIsland::AIsland()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AIsland::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AIsland::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AIsland::SetIslandActor(AActor* actor)
{
	IslandMeshActor = actor;
	FVector extents = FVector::ZeroVector;
	FVector origin = FVector::ZeroVector;
	actor->GetActorBounds(true, origin, extents);
	IslandExtent = FVector(extents.X + ExtraExtent, extents.Y + ExtraExtent, extents.Z + ExtraExtent);
}

void AIsland::GetUVBoundsOfActor(AActor* actor, FVector2D& uvMin, FVector2D& uvMax, float outlineDraw)
{
	if(!actor)
		return;
	FVector actorLocation = actor->GetActorLocation();
	FVector islandLocation = GetActorLocation();
	FVector actorOrigin = FVector();
	FVector actorExtents = FVector();
	actor->GetActorBounds(true, actorOrigin, actorExtents);
	
	float uvPadding = ( FMath::Min(actorExtents.X, actorExtents.Y)/ FMath::Min(IslandExtent.X, IslandExtent.Y)) * outlineDraw;
	FVector2D uvOffset = FVector2D(uvPadding, uvPadding)/2;
	
	FVector actorMin = actorOrigin - actorExtents;
	FVector actorMax = actorOrigin + actorExtents;
	FVector islandMax = islandLocation + IslandExtent;
	FVector islandMin = islandLocation - IslandExtent;
	float uMin = UKismetMathLibrary::MapRangeClamped(actorMin.X, islandMin.X, islandMax.X, 0, 1);
	float vMin = UKismetMathLibrary::MapRangeClamped(actorMin.Y, islandMin.Y, islandMax.Y, 0, 1);
	float uMax = UKismetMathLibrary::MapRangeClamped(actorMax.X, islandMin.X, islandMax.X, 0, 1);
	float vMax = UKismetMathLibrary::MapRangeClamped(actorMax.Y, islandMin.Y, islandMax.Y, 0, 1);
	uvMin = FVector2D(uMin, vMin) - uvOffset;
	uvMax = FVector2D(uMax,  vMax) + uvOffset;
}
bool AIsland::GetUVPositionOfActor(AActor* actor, FVector2D& uvPosition)
{
	if(!actor)
		return false;
	FVector actorLocation = actor->GetActorLocation();
	FVector islandLocation = GetActorLocation();
	FVector islandMax = islandLocation + IslandExtent;
	FVector islandMin = islandLocation - IslandExtent;
	float u = UKismetMathLibrary::MapRangeUnclamped(actorLocation.X, islandMin.X, islandMax.X, 0, 1);
	float v = UKismetMathLibrary::MapRangeUnclamped(actorLocation.Y, islandMin.Y, islandMax.Y, 0, 1);
	if(u < 0 || u > 1 || v < 0 || v > 1)
		return false;
	uvPosition = FVector2D(u, v);
	return true;
}

void AIsland::DrawMaterialToTarget(UTextureRenderTarget2D* renderTarget, UMaterialInterface* material, FVector2D uvMin,
	FVector2D uvMax)
{
	if(!renderTarget || !material)
		return;

	UCanvas* canvas = nullptr;
	FVector2D size = FVector2D();
	FDrawToRenderTargetContext context = FDrawToRenderTargetContext();
	UKismetRenderingLibrary::BeginDrawCanvasToRenderTarget(GetWorld(), renderTarget,canvas,size,context);
	FVector2D screenSize = (uvMax - uvMin) * size;
	FVector2D screenCenter = (uvMax + uvMin) * size / 2;
	canvas->K2_DrawMaterial(material, screenCenter, screenSize, FVector2D(0, 0), FVector2D(1, 1));
	UKismetRenderingLibrary::EndDrawCanvasToRenderTarget(GetWorld(), context);
}

void AIsland::DrawActorToTarget(UTextureRenderTarget2D* renderTarget, UMaterialInterface* material, AActor* actor,
	float outlineDraw)
{
	if(!renderTarget || !material || !actor)
		return;
	FVector2D uvMin = FVector2D();
	FVector2D uvMax = FVector2D();
	GetUVBoundsOfActor(actor, uvMin, uvMax, outlineDraw);
	DrawMaterialToTarget(renderTarget, material, uvMin, uvMax);
}
