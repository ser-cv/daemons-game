// For Daemons and something else videogame purpose only

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "DGCharacterBase.h"
#include "DGMechCharacter.generated.h"

UCLASS()
class DAEMONS_API ADGMechCharacter : public ADGCharacterBase
{
    GENERATED_BODY()

    void PossessedBy(AController* NewController);
    virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

protected:
    virtual void Interact() override;

    virtual void HandleAcceleration() override;
};
