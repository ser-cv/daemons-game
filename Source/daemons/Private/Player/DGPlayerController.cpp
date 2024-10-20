// For Daemons and something else videogame purpose only

#include "Player/DGPlayerController.h"
#include "Kismet/GameplayStatics.h"
#include "Player/DGHumanCharacter.h"

void ADGPlayerController::CreateAndPossessMech(FTransform MechDummyTransform)
{
    ACharacter* CurrentCharacter = UGameplayStatics::GetPlayerCharacter(this, 0);
    if (Cast<ADGHumanCharacter>(CurrentCharacter))
    {
        FVector MechSpawnLocation = MechDummyTransform.GetLocation();
        FRotator SpawnRotation = MechDummyTransform.Rotator();
        
        FActorSpawnParameters SpawnParameters;
        SpawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
        ACharacter* NewCharacter = GetWorld()->SpawnActor<ACharacter>(MechCharacter, MechSpawnLocation, SpawnRotation, SpawnParameters);
        Possess(NewCharacter);
        CurrentCharacter->Destroy();
    }
}