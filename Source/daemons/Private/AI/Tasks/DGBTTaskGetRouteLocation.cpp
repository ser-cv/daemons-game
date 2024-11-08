// For Daemons and something else videogame purpose only


#include "AI/Tasks/DGBTTaskGetRouteLocation.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AIController.h"
#include "AI/DGAICharacter.h"

UDGBTTaskGetRouteLocation::UDGBTTaskGetRouteLocation()
{
    NodeName = "Get Patrol Route Location";
    PatrolRouteLocationKey.AddVectorFilter(this, "Patrol Location");
}

EBTNodeResult::Type UDGBTTaskGetRouteLocation::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
    const auto AIController = OwnerComp.GetAIOwner();
    if (!AIController) return EBTNodeResult::Failed;

    const auto Blackboard = OwnerComp.GetBlackboardComponent();
    if (!Blackboard) return EBTNodeResult::Failed;

    const auto AICharacter = Cast<ADGAICharacter>(AIController->GetPawn());
    if (!AICharacter) return EBTNodeResult::Failed;

    const FVector PatrolRouteLocation = AICharacter->GetPatrolRouteLocation();
    Blackboard->SetValueAsVector(PatrolRouteLocationKey.SelectedKeyName, PatrolRouteLocation);

    return EBTNodeResult::Succeeded;
}
