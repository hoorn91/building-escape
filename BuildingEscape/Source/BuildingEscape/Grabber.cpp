// Fill out your copyright notice in the Description page of Project Settings.

#include "BuildingEscape.h"
#include "Grabber.h"

// Empty macro for being extra clear of out variables
#define OUT

// Sets default values for this component's properties
UGrabber::UGrabber()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UGrabber::BeginPlay()
{
	Super::BeginPlay();

    FindPhysicsHandleComponent();
    SetupInputComponent();
}

void UGrabber::FindPhysicsHandleComponent()
{
    /// Look for attached Physics Handle
    PhysicsHandle = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();
    if (PhysicsHandle)
    {
        // Physics handle is found
    }
    else
    {
        UE_LOG(LogTemp, Error, TEXT("Cannot find Physics Handle component on %s"), *GetOwner()->GetName());
    }
}

void UGrabber::SetupInputComponent()
{
    /// Look for attached Input Component (Appears at run time)
    InputComponent = GetOwner()->FindComponentByClass<UInputComponent>();

    if (InputComponent)
    {
        ///Component found
        /// Bind input axis
        InputComponent->BindAction("Grab", IE_Pressed, this, &UGrabber::Grab);
        InputComponent->BindAction("Grab", IE_Released, this, &UGrabber::Release);
    }
    else
    {
        UE_LOG(LogTemp, Error, TEXT("Cannot find Input Component on %s"), *GetOwner()->GetName());
    }
}

// Called every frame
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
    /// Get player view point this tick
    FVector PlayerViewPointLocation;
    FRotator PlayerViewPointRotation;
    GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(
        OUT PlayerViewPointLocation,
        OUT PlayerViewPointRotation
    );

    FVector LineTraceEnd = PlayerViewPointLocation + (PlayerViewPointRotation.Vector() * Reach);
    //If the physics handle is attached
    if (PhysicsHandle->GrabbedComponent)
    {
        PhysicsHandle->SetTargetLocation(LineTraceEnd);
    }
        // mode the object that we're holding


    // See what object we hit
	/*AActor* ActorHit = Hit.GetActor();
	if (ActorHit)
	{
		if (DEBUG) UE_LOG(LogTemp, Warning, TEXT("%s"), *ActorHit->GetName());

		// If we hit and object and hold the F key, carry the object
		if (Player->IsInputKeyDown(EKeys::F))
		{
			ActorHit->SetActorLocation(LineTraceEnd);
		}
		
	}*/

	// ...
}

void UGrabber::Grab()
{
    FHitResult Hit = GetFirstPhysicsBodyInReach();
    //AActor* ActorHit = GetFirstPhysicsBodyInReach().GetActor();
    
    UPrimitiveComponent* Component = Hit.GetComponent();
    AActor* ActorHit = Hit.GetActor();

    if (ActorHit)
    {
        PhysicsHandle->GrabComponent(
            Component,
            NAME_None,
            ActorHit->GetActorLocation(),
            true
        );
    }
}

void UGrabber::Release()
{
    PhysicsHandle->ReleaseComponent();
    //UE_LOG(LogTemp, Warning, TEXT("Release"))
}

const FHitResult UGrabber::GetFirstPhysicsBodyInReach()
{
    FVector PlayerViewPointLocation;
    FRotator PlayerViewPointRotation;
    GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(
        OUT PlayerViewPointLocation,
        OUT PlayerViewPointRotation
    );

    FVector LineTraceEnd = PlayerViewPointLocation + (PlayerViewPointRotation.Vector() * Reach);

    /// Set up query parameters
    FCollisionQueryParams TraceParameters(FName(TEXT("")), false, GetOwner());
    FHitResult Hit;
    /// Line trace (AKA ray-cast)
    GetWorld()->LineTraceSingleByObjectType(
        OUT Hit,
        PlayerViewPointLocation,
        LineTraceEnd,
        FCollisionObjectQueryParams(ECollisionChannel::ECC_PhysicsBody),
        TraceParameters
    );
    return Hit;
}


