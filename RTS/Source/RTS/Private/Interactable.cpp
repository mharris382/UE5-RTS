// Fill out your copyright notice in the Description page of Project Settings.

#include "Interactable.h"
#include "UObject/ConstructorHelpers.h"
#include "Components/BoxComponent.h"
#include "Components/DecalComponent.h"
#include "Engine/StaticMesh.h"
#include "Kismet/KismetMathLibrary.h"

// Sets default values
AInteractable::AInteractable()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	Scene = CreateDefaultSubobject<USceneComponent>(TEXT("Scene"));
	RootComponent = Scene;

	BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MESH"));
	BaseMesh->SetupAttachment(RootComponent);
	
	Decal = CreateDefaultSubobject<UDecalComponent>(TEXT("Decal"));
	Decal->SetupAttachment(RootComponent);
	Decal->SetRelativeRotation(FRotator(-90,0,0));

	
	Box = CreateDefaultSubobject<UBoxComponent>(TEXT("Collision"));
	Box->SetupAttachment(RootComponent);

	static ConstructorHelpers::FObjectFinder<UDataTable> DataTableAsset(TEXT("/Script/Engine.DataTable'/Game/Blueprint/Interactable/Data/DT_Buidables.DT_Buidables'"));

	if (DataTableAsset.Succeeded())
	{
		// Initialize your TObjectPtr<UDataTable> with the found data table
		SpawnKey = FDataTableRowHandle();
		SpawnKey.DataTable = DataTableAsset.Object;
	}
	else
	{
		//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("NO DataTable found at path /Game/Blueprint/Data/DT_Buildables.DT_Buildables'"));
	}

	static ConstructorHelpers::FObjectFinder<UMaterialInstance> DecalMat(TEXT("MaterialInstance'/Game/Blueprint/Interactable/Extras/MI_InvalidPlacement.MI_InvalidPlacement'"));
	if(DecalMat.Succeeded())
	{
		Decal->SetMaterial(0, DecalMat.Object);
	}

	
}

// Called when the game starts or when spawned
void AInteractable::BeginPlay()
{
	//error checking
	if (SpawnKey.DataTable) {
		if (SpawnKey.RowName == FName())
		{
			// Get the class name of the actor
			FString tn1 = GetClass()->GetName();
			FString msg1 = FString::Printf(TEXT("Missing row assignment on %s"), *tn1);
			//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, msg1);
		}
	}
	else
	{
		FString tn2 = GetClass()->GetName();
		FString msg2 = FString::Printf(TEXT("Missing data table assignment on %s"),  *tn2);
		//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, msg2);
	}
	
}

// Called every frame
void AInteractable::Tick(float DeltaTime)
{
	

}

void AInteractable::SetProgressionState(float progress)
{
	ProgressionState = progress;
	if (RequiresBuild) {
		Tags.Add(FName(TEXT("Build")));
		int32 index = UKismetMathLibrary::Min(UKismetMathLibrary::FFloor(ProgressionState), MeshList.Num()-1);
		if (!MeshList[index])
		{
			FString tn2 = GetClass()->GetName();
			FString msg1 = FString::Printf(TEXT("Null mesh in mesh list on class %s"),*tn2);
			//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, msg1);
		}
		BaseMesh->SetStaticMesh(MeshList[index]);
	}
}

void AInteractable::PlacementMode()
{
	EnabledGroundBlend = false;
	if (MeshList.Num() > 0)
	{
		BaseMesh->SetStaticMesh(MeshList[0]);
	}
	Tags.Add(FName(TEXT("PlacementMode")));
}

void AInteractable::TransformToTexture(FVector2D inVec, FVector2D& vec1, FVector2D& vec2)
{
	FVector v1 = ((GetActorLocation() + FVector(10000.0)) / FVector(20000.0)) * FVector(inVec.X);

	FVector origin;
	FVector extent;
	 GetActorBounds(false, origin, extent, false);
	 float v = (UKismetMathLibrary::Min(extent.X, extent.Y) / 10000.0) * inVec.X * OutlineDraw;
	 FVector fvec1 = v1 - FVector(v / 2.0);
	 vec1 = FVector2D(fvec1.X, fvec1.Y);
	 vec2 = FVector2D(v, v);
}

void AInteractable::UpdateBoxBounds()
{
	//compute size of mesh
	UStaticMesh* mesh = BaseMesh->GetStaticMesh();
	if (mesh)
	{
		float step = 100;
		FBox localBounds = mesh->GetBoundingBox();
		FVector min = localBounds.Min / 100.0;
		int xr = UKismetMathLibrary::Round(min.X);
		int yr = UKismetMathLibrary::Round(min.Y);
		int zr = UKismetMathLibrary::Round(min.Z);
		float stepX = xr * step;
		float stepY = yr * step;
		float stepXY = UKismetMathLibrary::Max(UKismetMathLibrary::Max(stepX, stepY), step);
		float stepZ = UKismetMathLibrary::Max(step, zr * step);
		FVector bounds = (FVector(stepXY, stepXY, stepZ) * BoundScale) + (FVector(step, step, step) * BoundGap);
		Box->SetBoxExtent(bounds, true);
		
		Box->SetWorldRotation(UKismetMathLibrary::MakeRotFromX(FVector(1, 0, 0)));
		Decal->SetRelativeScale3D(FVector(1, bounds.X, bounds.Y));
	}
}

void AInteractable::VerifyReferencesSet()
{
	
}

void AInteractable::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
{
	VerifyReferencesSet();
	UpdateBoxBounds();
}

void AInteractable::PostLoad()
{
	Super::PostLoad();
	VerifyReferencesSet();
	UpdateBoxBounds();
}

