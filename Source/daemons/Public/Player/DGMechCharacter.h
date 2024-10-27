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
    FTimerHandle LeaveMechTimerHandle;

    virtual void HandleCrouch() override;
    virtual void Interact() override;
    virtual void CancelInteraction() override;

    virtual void HandleAcceleration() override;
    virtual void Sprint() override;
    virtual void StopSprinting() override;

    UPROPERTY(EditAnywhere, Category = "Parameters")
    float MechExitDelay{0.7f};
};
