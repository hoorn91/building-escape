// Fill out your copyright notice in the Description page of Project Settings.

#include "BuildingEscape.h"
#include "PositionReport.h"


// Sets default values for this component's properties
UPositionReport::UPositionReport()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
    
	// ...
}


// Called when the game starts
void UPositionReport::BeginPlay()
{
	Super::BeginPlay();
    AActor* Owner = GetOwner();
    FTransform  Transform = Owner->GetActorTransform();
    
    FString Location = Transform.GetLocation().ToString();
    FVector* veloc = new FVector();
    veloc->Set(0.1f,0.0f,0.0f);
    
    Owner->GetRootComponent()->ComponentVelocity = *veloc;
    UE_LOG(LogTemp, Warning, TEXT("%s Is at %s"), *Owner->GetName(), *Location);
	// ...
	
}


// Called every frame
void UPositionReport::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

