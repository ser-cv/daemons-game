// For Daemons and something else videogame purpose only

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "DGPlayerController.generated.h"

UCLASS()
class DAEMONS_API ADGPlayerController : public APlayerController
{
    GENERATED_BODY()

public:
    void CreateAndPossessMech(FTransform MechDummyTransform);

    void CreateAndPossessHuman();

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Characters")
    TSubclassOf<AActor> MechDummy;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Characters")
    TSubclassOf<ACharacter> MechCharacter;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Characters")
    TSubclassOf<ACharacter> HumanCharacter;
};
