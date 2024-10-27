// For Daemons and something else videogame purpose only


#include "AI/Tasks/DGBTTaskRememberLastLocation.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AIController.h"
#include "Perception/AIPerceptionComponent.h"

UDGBTTaskRememberLastLocation::UDGBTTaskRememberLastLocation() 
{
    NodeName = "Remember Last Location";
    LastSeenLocationKey.AddVectorFilter(this, "Last Location");
}

EBTNodeResult::Type UDGBTTaskRememberLastLocation::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
    const auto AIController = OwnerComp.GetAIOwner();
    if (!AIController) return EBTNodeResult::Failed;

    const auto Blackboard = OwnerComp.GetBlackboardComponent();
    if (!Blackboard) return EBTNodeResult::Failed;

    const auto InstigatorActor = Cast<AActor>(Blackboard->GetValueAsObject(InstigatorKey.SelectedKeyName));
    const auto PerceptionComponent = AIController->PerceptionComponent;
    if (!PerceptionComponent) return EBTNodeResult::Failed;

    const FVector LastLocation = PerceptionComponent->GetActorLocation(*InstigatorActor);
    Blackboard->SetValueAsVector(LastSeenLocationKey.SelectedKeyName, LastLocation);
    return EBTNodeResult::Succeeded;
}
