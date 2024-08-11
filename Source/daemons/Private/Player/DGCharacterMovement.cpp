// For Daemons and something else videogame purpose only

#include "Player/DGCharacterMovement.h"

void UDGCharacterMovement::UpdateCharacterStateBeforeMovement(float DeltaSeconds) 
{
    const bool bIsSprinting{IsCustomMovementMode(CMOVE_Sprint)};

    if (bWantsToSprint
        && !Velocity.IsNearlyZero())
    {
        SetMovementMode(MOVE_Custom, CMOVE_Sprint);
    }
    if (!bWantsToSprint
        && bIsSprinting)
    {
        SetMovementMode(DefaultLandMovementMode);
    }

}

float UDGCharacterMovement::GetMaxSpeed() const
{
    const float MaxSpeed = Super::GetMaxSpeed();
	if (MovementMode != MOVE_Custom)
	{
		return MaxSpeed;
	}

	switch (CustomMovementMode)
	{
		case CMOVE_Sprint : return SprintSpeed;
		default: return MaxSpeed;
	}
}

void UDGCharacterMovement::InitializeComponent() 
{
    Super::InitializeComponent();
}

void UDGCharacterMovement::PhysCustom(float DeltaTime, int32 Iterations) 
{
    Super::PhysCustom(DeltaTime, Iterations);

	switch (CustomMovementMode)
	{
        case CMOVE_Sprint:
			PhysSprint(DeltaTime, Iterations);
			break;

		default:
			UE_LOG(LogTemp, Error, TEXT("Invalid Movement Mode"))
	}
}

void UDGCharacterMovement::PhysSprint(float DeltaTime, int32 Iterations) 
{
    PhysWalking(DeltaTime, Iterations);
}

bool UDGCharacterMovement::IsCustomMovementMode(const ECustomMovementMode InCustomMovementMode) const
{
    return MovementMode == MOVE_Custom && CustomMovementMode == InCustomMovementMode;
}
