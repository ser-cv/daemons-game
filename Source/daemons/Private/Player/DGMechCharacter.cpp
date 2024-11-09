// For Daemons and something else videogame purpose only


#include "Player/DGMechCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Interfaces/DGInteractionInterface.h"
#include "Player/DGPlayerController.h"

void ADGMechCharacter::PossessedBy(AController* NewController) 
{
    Super::PossessedBy(NewController);
}

void ADGMechCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) 
{
    Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void ADGMechCharacter::HandleAcceleration()
{
    Dash();
}

void ADGMechCharacter::Sprint() {}

void ADGMechCharacter::StopSprinting() {}

void ADGMechCharacter::HandleCrouch() {}

void ADGMechCharacter::Interact()
{
    if (UWorld* CurrentWorld = GetWorld())
    {
        CurrentWorld->GetTimerManager().SetTimer(
            LeaveMechTimerHandle, PlayerController, &ADGPlayerController::CreateAndPossessHuman, MechExitDelay, false);
    }
}

void ADGMechCharacter::CancelInteraction() 
{
    GetWorld()->GetTimerManager().ClearTimer(LeaveMechTimerHandle);
}
