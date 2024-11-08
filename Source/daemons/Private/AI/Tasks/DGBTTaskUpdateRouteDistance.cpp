// For Daemons and something else videogame purpose only


#include "AI/Tasks/DGBTTaskUpdateRouteDistance.h"
#include "AIController.h"
#include "AI/DGAICharacter.h"

UDGBTTaskUpdateRouteDistance::UDGBTTaskUpdateRouteDistance() 
{
    NodeName = "Update Patrol Route Distance";
}

EBTNodeResult::Type UDGBTTaskUpdateRouteDistance::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
    const auto AIController = OwnerComp.GetAIOwner();
    if (!AIController) return EBTNodeResult::Failed;

    const auto AICharacter = Cast<ADGAICharacter>(AIController->GetPawn());
    if (!AICharacter) return EBTNodeResult::Failed;

    AICharacter->UpdatePatrolRouteDistance();
    return EBTNodeResult::Succeeded;
}
