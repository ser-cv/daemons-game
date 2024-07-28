// For Daemons and something else videogame purpose only


#include "Game/DGGameModeBase.h"
#include "Player/DGFirstPersonCharacter.h"
#include "Player/DGPlayerController.h"

ADGGameModeBase::ADGGameModeBase() 
{
    DefaultPawnClass = ADGFirstPersonCharacter::StaticClass();
    PlayerControllerClass = ADGPlayerController::StaticClass();
}
