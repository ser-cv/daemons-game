// For Daemons and something else videogame purpose only


#include "Player/DGMechCharacter.h"

//
//void ADGMechCharacter::Move(const FInputActionValue& Value) 
//{
//
//}
//
//void ADGMechCharacter::Look(const FInputActionValue& Value) 
//{
//
//}
//
//void ADGMechCharacter::HandleAcceleration() 
//{
//
//}
//
//void ADGMechCharacter::Dash() 
//{
//
//}
//
//void ADGMechCharacter::Interact() 
//{
//
//}
//
//void ADGMechCharacter::CancelInteraction() 
//{
//
//}

void ADGMechCharacter::PossessedBy(AController* NewController) 
{
    Super::PossessedBy(NewController);
}

void ADGMechCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) 
{
    Super::SetupPlayerInputComponent(PlayerInputComponent);
}
