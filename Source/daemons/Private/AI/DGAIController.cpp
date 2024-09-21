// For Daemons and something else videogame purpose only


#include "AI/DGAIController.h"
#include "AI/DGEnemy.h"

ADGAIController::ADGAIController() {}

void ADGAIController::OnPossess(APawn* InPawn)
{
    Super::OnPossess(InPawn);

    if (const auto AIEnemy = Cast<ADGEnemy>(InPawn))
    {
        RunBehaviorTree(AIEnemy->BehaviorTreeAsset);
    }
}
