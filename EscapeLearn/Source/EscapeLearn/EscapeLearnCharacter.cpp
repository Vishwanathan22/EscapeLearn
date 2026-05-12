// Copyright Epic Games, Inc. All Rights Reserved.

#include "EscapeLearnCharacter.h"

#include "Animation/AnimInstance.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "EnhancedInputComponent.h"
#include "InputActionValue.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "EscapeLearn.h"

AEscapeLearnCharacter::AEscapeLearnCharacter()
{
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(55.f, 96.0f);

	// Create the first-person mesh (visible only to owning player)
	FirstPersonMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("First Person Mesh"));
	FirstPersonMesh->SetupAttachment(GetMesh());
	FirstPersonMesh->SetOnlyOwnerSee(true);
	FirstPersonMesh->FirstPersonPrimitiveType = EFirstPersonPrimitiveType::FirstPerson;
	FirstPersonMesh->SetCollisionProfileName(FName("NoCollision"));
	FirstPersonMesh->SetHiddenInGame(true);

	// Create the first-person camera
	FirstPersonCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("First Person Camera"));
	FirstPersonCameraComponent->SetupAttachment(FirstPersonMesh, FName("head"));
	FirstPersonCameraComponent->SetRelativeLocationAndRotation(
		FVector(-2.8f, 5.89f, 0.0f),
		FRotator(0.0f, 90.0f, -90.0f)
	);
	FirstPersonCameraComponent->bUsePawnControlRotation = true;
	FirstPersonCameraComponent->bEnableFirstPersonFieldOfView = true;
	FirstPersonCameraComponent->bEnableFirstPersonScale = true;
	FirstPersonCameraComponent->FirstPersonFieldOfView = 70.0f;
	FirstPersonCameraComponent->FirstPersonScale = 0.6f;

	// Configure third-person mesh
	GetMesh()->SetOwnerNoSee(true);
	GetMesh()->FirstPersonPrimitiveType = EFirstPersonPrimitiveType::WorldSpaceRepresentation;

	// Adjust capsule
	GetCapsuleComponent()->SetCapsuleSize(34.0f, 96.0f);

	// Character movement configuration
	GetCharacterMovement()->BrakingDecelerationFalling = 1500.0f;
	GetCharacterMovement()->AirControl = 0.5f;
}

void AEscapeLearnCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	if (UEnhancedInputComponent* EnhancedInputComponent =
		Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		// Jump
		EnhancedInputComponent->BindAction(
			JumpAction, ETriggerEvent::Started, this, &AEscapeLearnCharacter::DoJumpStart);
		EnhancedInputComponent->BindAction(
			JumpAction, ETriggerEvent::Completed, this, &AEscapeLearnCharacter::DoJumpEnd);

		// Movement
		EnhancedInputComponent->BindAction(
			MoveAction, ETriggerEvent::Triggered, this, &AEscapeLearnCharacter::MoveInput);

		// Look
		EnhancedInputComponent->BindAction(
			LookAction, ETriggerEvent::Triggered, this, &AEscapeLearnCharacter::LookInput);
		EnhancedInputComponent->BindAction(
			MouseLookAction, ETriggerEvent::Triggered, this, &AEscapeLearnCharacter::LookInput);
	}
	else
	{
		UE_LOG(
			LogEscapeLearn,
			Error,
			TEXT("'%s' Failed to find an Enhanced Input Component!"),
			*GetNameSafe(this)
		);
	}
}

void AEscapeLearnCharacter::MoveInput(const FInputActionValue& Value)
{
	const FVector2D MovementVector = Value.Get<FVector2D>();
	DoMove(MovementVector.X, MovementVector.Y);
}

void AEscapeLearnCharacter::LookInput(const FInputActionValue& Value)
{
	const FVector2D LookAxisVector = Value.Get<FVector2D>();
	DoAim(LookAxisVector.X, LookAxisVector.Y);
}

void AEscapeLearnCharacter::DoAim(float Yaw, float Pitch)
{
	if (GetController())
	{
		AddControllerYawInput(Yaw);
		AddControllerPitchInput(Pitch);
	}
}

void AEscapeLearnCharacter::DoMove(float Right, float Forward)
{
	if (GetController())
	{
		AddMovementInput(GetActorRightVector(), Right);
		AddMovementInput(GetActorForwardVector(), Forward);
	}
}

void AEscapeLearnCharacter::DoJumpStart()
{
	Jump();
}

void AEscapeLearnCharacter::DoJumpEnd()
{
	StopJumping();
}
