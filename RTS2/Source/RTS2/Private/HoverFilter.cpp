// Fill out your copyright notice in the Description page of Project Settings.


#include "HoverFilter.h"

// Sets default values for this component's properties
UHoverFilter::UHoverFilter()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

TArray<AActor*> UHoverFilter::FilterHoveredActors(const TArray<AActor*>& Actors)
{
	TArray<AActor*> FilteredActors;

	for (AActor* Actor : Actors)
	{
		if(Actor && !ShouldFilterActor(Actor))
		{
			FilteredActors.Add(Actor);
		}
	}
	return FilteredActors;
}


bool UHoverFilter::ShouldFilterActor_Implementation(AActor* actor)
{
	return false;
}

// Called when the game starts
void UHoverFilter::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UHoverFilter::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

