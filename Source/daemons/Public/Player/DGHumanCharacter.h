// For Daemons and something else videogame purpose only

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "DGCharacterBase.h"
#include "DGHumanCharacter.generated.h"

UCLASS()
class DAEMONS_API ADGHumanCharacter : public ADGCharacterBase
{
    GENERATED_BODY()

public:
    void PossessedBy(AController* NewController);
    virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
};
