// Fill out your copyright notice in the Description page of Project Settings.

#include "BuildingEscape.h"
#include "OpenDoor.h"


// Sets default values for this component's properties
UOpenDoor::UOpenDoor()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UOpenDoor::BeginPlay()
{
	Super::BeginPlay();
    ActorThatOpens = GetWorld()->GetFirstPlayerController()->GetPawn();

    // Find owning actor
    Owner = GetOwner();
    // ...
	
}

void UOpenDoor::OpenDoor()
{
    Owner->SetActorRotation(FRotator(0.0f, OpenAngle, 0.0f));
}

void UOpenDoor::CloseDoor()
{
    Owner->SetActorRotation(FRotator(0.0f, 0.0f, 0.0f));
}

// Called every frame
void UOpenDoor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
    // Poll the Trigger Volume
    // If the Actor that opens is in the volume then open the door
    if (PressurePlate->IsOverlappingActor(ActorThatOpens))
    {
        OpenDoor();
        TimeDoorLastOpened = GetWorld()->GetTimeSeconds();
    }
    
	// If the door has been opened for the amount of time specified in DoorCloseDelay then shut the door again
    if ((TimeDoorLastOpened > 0.0f) && (GetWorld()->GetTimeSeconds() - TimeDoorLastOpened) >= DoorCloseDelay)
    {
        CloseDoor();
        TimeDoorLastOpened = 0.0f;
    }
	// ...
}

