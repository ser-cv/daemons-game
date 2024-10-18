// For Daemons and something else videogame purpose only

#include "AI/DGAIController.h"
#include "AI/DGAICharacter.h"
#include "Perception/AIPerceptionComponent.h"

ADGAIController::ADGAIController()
{
    SetPerceptionComponent(*CreateDefaultSubobject<UAIPerceptionComponent>("Perception"));
}

void ADGAIController::OnPossess(APawn* InPawn)
{
    Super::OnPossess(InPawn);

    if (const auto AICharacter = Cast<ADGAICharacter>(InPawn))
    {
        RunBehaviorTree(AICharacter->BehaviorTreeAsset);
    }

    SetGenericTeamId(FGenericTeamId(5));
}

ETeamAttitude::Type ADGAIController::GetTeamAttitudeTowards(const AActor& Other) const
{
    const auto PlayerPawn = Cast<APawn>(&Other);
    if (const auto PlayerController = Cast<APlayerController>(PlayerPawn->GetController()))
    {
        return ETeamAttitude::Hostile;
    }

    return Super::GetTeamAttitudeTowards(Other);
}
