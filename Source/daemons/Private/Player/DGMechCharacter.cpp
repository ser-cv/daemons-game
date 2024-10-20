// For Daemons and something else videogame purpose only


#include "Player/DGMechCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Interfaces/DGInteractionInterface.h"

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

void ADGMechCharacter::Interact() {
   
}

void ADGMechCharacter::CancelInteraction() {}
