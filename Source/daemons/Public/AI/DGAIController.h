// For Daemons and something else videogame purpose only

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "DGAIController.generated.h"

class UDGAIPerceptionComponent;

UCLASS()
class DAEMONS_API ADGAIController : public AAIController
{
    GENERATED_BODY()

public:
    ADGAIController();

protected:
    virtual void OnPossess(APawn* InPawn) override;

    virtual ETeamAttitude::Type GetTeamAttitudeTowards(const AActor& Other) const override;
};
