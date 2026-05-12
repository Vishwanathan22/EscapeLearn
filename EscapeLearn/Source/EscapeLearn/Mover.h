#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Mover.generated.h"

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class ESCAPELEARN_API UMover : public UActorComponent
{
	GENERATED_BODY()

public:
	UMover();

	UPROPERTY(EditAnywhere, Category = "Mover")
	FVector StartLocation;

	UPROPERTY(EditAnywhere, Category = "Mover")
	FVector TargetLocation;

	UPROPERTY(EditAnywhere, Category = "Mover")
	FVector MoveOffset;

	UPROPERTY(EditAnywhere, Category = "Mover")
	float MoveTime = 4.0f;

	UPROPERTY(VisibleAnywhere, Category = "Mover")
	bool ReachedTarget = false;

protected:
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, Category = "Mover")
	bool ShouldMove = false; // Kept for debugging/visualization, not used for gating

public:
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	bool GetShouldMove();
	void SetShouldMove(bool NewShouldMove);
};
