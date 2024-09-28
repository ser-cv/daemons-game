// For Daemons and something else videogame purpose only

#include "Player/DGHumanCharacter.h"

void ADGHumanCharacter::PossessedBy(AController* NewController) 
{
    Super::PossessedBy(NewController);
}

void ADGHumanCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
    Super::SetupPlayerInputComponent(PlayerInputComponent);
}
