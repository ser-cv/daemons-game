// For Daemons and something else videogame purpose only

#include "Player/DGPlayerController.h"
#include "Kismet/GameplayStatics.h"
#include "Player/DGHumanCharacter.h"
#include "Player/DGMechCharacter.h"
#include "Player/MechDummy.h"

void ADGPlayerController::CreateAndPossessMech(FTransform MechDummyTransform)
{
    
    if (ADGHumanCharacter* CurrentCharacter = Cast<ADGHumanCharacter>(GetCharacter()))
    {
        FVector MechSpawnLocation = MechDummyTransform.GetLocation();
        FRotator MechSpawnRotation = MechDummyTransform.Rotator();
        
        FActorSpawnParameters SpawnParameters;
        SpawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
       
        ACharacter* NewCharacter = GetWorld()->SpawnActor<ACharacter>(MechCharacter, MechSpawnLocation, MechSpawnRotation, SpawnParameters);
        Possess(NewCharacter);
        CurrentCharacter->Destroy();
    }
}

void ADGPlayerController::CreateAndPossessHuman()
{
    if (ADGMechCharacter* CurrentCharacter = Cast<ADGMechCharacter>(GetCharacter()))
    {
        FVector HumanSpawnLocation = CurrentCharacter->GetActorLocation();
        FRotator HumanSpawnRotation = CurrentCharacter->GetActorRotation();

        FActorSpawnParameters SpawnParameters;
        SpawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
        
        ACharacter* NewCharacter = GetWorld()->SpawnActor<ACharacter>(HumanCharacter, HumanSpawnLocation, HumanSpawnRotation, SpawnParameters);
        Possess(NewCharacter);
        CurrentCharacter->Destroy();

        GetWorld()->SpawnActor<AActor>(MechDummy, HumanSpawnLocation, HumanSpawnRotation, SpawnParameters);
    }
}