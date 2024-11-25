// For Daemons and something else videogame purpose only

#include "UsableActors/DGSpawner.h"

ADGSpawner::ADGSpawner()
{
    PrimaryActorTick.bCanEverTick = true;
}

void ADGSpawner::BeginPlay()
{
    Super::BeginPlay();
}

void ADGSpawner::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
}
