// For Daemons and something else videogame purpose only


#include "Game/DGGameModeBase.h"
#include "Player/DGPlayerController.h"

ADGGameModeBase::ADGGameModeBase() 
{
    PlayerControllerClass = ADGPlayerController::StaticClass();
}
