// For Daemons and something else videogame purpose only


#include "AI/DGFindEnemyService.h"
#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Components/DGAIPerceptionComponent.h"

UDGFindEnemyService::UDGFindEnemyService() 
{
    NodeName = "Find enemy";
}

void UDGFindEnemyService::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) 
{
    const auto Blackboard = OwnerComp.GetBlackboardComponent(); 
    if (Blackboard)
    {
        const auto Controller = OwnerComp.GetAIOwner();
        const auto PerceptionComponent = Controller->FindComponentByClass<UDGAIPerceptionComponent>();
        if (PerceptionComponent)
        {
            const auto FoundAim = PerceptionComponent->GetClosestEnemy();
            Blackboard->SetValueAsObject(AimPawnKey.SelectedKeyName, FoundAim);
            if (FoundAim)
            {
                Blackboard->SetValueAsVector(AimPawnLocationKey.SelectedKeyName, FoundAim->GetActorLocation());
            }
        }
    }

    Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);
}
