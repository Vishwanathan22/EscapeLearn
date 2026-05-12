#include "Mover.h"
#include "Math/UnrealMathUtility.h"

// Sets default values
UMover::UMover()
{
	PrimaryComponentTick.bCanEverTick = true;
}

// Called when the game starts
void UMover::BeginPlay()
{
	Super::BeginPlay();

	if (GetOwner() && GetOwner()->GetRootComponent())
	{
		GetOwner()->GetRootComponent()->SetMobility(EComponentMobility::Movable);
	}

	StartLocation = GetOwner()->GetActorLocation();
	TargetLocation = StartLocation;
}

// Called every frame
void UMover::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (!GetOwner())
	{
		return;
	}

	FVector CurrentLocation = GetOwner()->GetActorLocation();

	// Tolerance prevents floating point lock
	ReachedTarget = CurrentLocation.Equals(TargetLocation, 1.0f);

	// Movement always runs until the current target is reached
	if (!ReachedTarget)
	{
		float Speed = MoveOffset.Length() / MoveTime;
		FVector NewLocation = FMath::VInterpConstantTo(CurrentLocation, TargetLocation, DeltaTime, Speed);
		GetOwner()->SetActorLocation(NewLocation);
	}
}

bool UMover::GetShouldMove()
{
	return ShouldMove;
}

void UMover::SetShouldMove(bool NewShouldMove)
{
	ShouldMove = NewShouldMove;

	// Trigger decides the target, not whether movement runs
	if (ShouldMove)
	{
		TargetLocation = StartLocation + MoveOffset;
	}
	else
	{
		TargetLocation = StartLocation;
	}
}
