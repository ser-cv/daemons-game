// For Daemons and something else videogame purpose only


#include "AI/Tasks/DGBTTaskFindPatrolRoute.h"
#include "AIController.h"
#include "AI/DGAICharacter.h"

UDGBTTaskFindPatrolRoute::UDGBTTaskFindPatrolRoute() 
{
    NodeName = "Find Patrol Route";
}

EBTNodeResult::Type UDGBTTaskFindPatrolRoute::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
    const auto AIController = OwnerComp.GetAIOwner();
    if (!AIController) return EBTNodeResult::Failed;

    const auto AICharacter = Cast<ADGAICharacter>(AIController->GetPawn());
    if (!AICharacter) return EBTNodeResult::Failed;

    AICharacter->GetDistanceClosestToLocation();
    return EBTNodeResult::Succeeded;
}
