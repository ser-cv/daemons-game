// For Daemons and something else videogame purpose only

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DGCoreTypes.h"
#include "AI/DGAICharacter.h"
#include "DGSpawner.generated.h"

class ADGAICharacter;

UCLASS()
class DAEMONS_API ADGSpawner : public AActor
{
    GENERATED_BODY()

public:
    ADGSpawner();

    EPhase WhichGamePhaseSelected() const { return SelectedGamePhase; }
    bool CanSpawn() { return true; }
    UClass* ClassForSpawning() const { return AICharacterClass.Get(); }

protected:
    UPROPERTY(EditAnywhere, BlueprintReadOnly)
    EPhase SelectedGamePhase{EPhase::No_Phase};

    UPROPERTY(EditAnywhere, BlueprintReadOnly)
    TSubclassOf<ADGAICharacter> AICharacterClass;

    virtual void BeginPlay() override;

public:
    virtual void Tick(float DeltaTime) override;
};
