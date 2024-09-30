// For Daemons and something else videogame purpose only


#include "AI/DGAIController.h"
#include "AI/DGEnemy.h"
#include "Components/DGAIPerceptionComponent.h"

ADGAIController::ADGAIController() 
{
    DGAIPerceptionComponent = CreateDefaultSubobject<UDGAIPerceptionComponent>("AIPerceptionComponent");
    SetPerceptionComponent(*DGAIPerceptionComponent.Get());
}

void ADGAIController::OnPossess(APawn* InPawn)
{
    Super::OnPossess(InPawn);

    if (const auto AIEnemy = Cast<ADGEnemy>(InPawn))
    {
        RunBehaviorTree(AIEnemy->BehaviorTreeAsset);
    }
}
