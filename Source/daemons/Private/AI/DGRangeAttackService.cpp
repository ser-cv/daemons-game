// For Daemons and something else videogame purpose only


#include "AI/DGRangeAttackService.h"
#include "Interfaces/DGCombatInterface.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AIController.h"

UDGRangeAttackService::UDGRangeAttackService() 
{
    NodeName = "Range Attack Service";
}

void UDGRangeAttackService::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) 
{
    const auto AIController = OwnerComp.GetAIOwner();
    const auto Blackboard = OwnerComp.GetBlackboardComponent();

    const bool bHasAim = Blackboard && Blackboard->GetValueAsObject(AimPawnKey.SelectedKeyName);

    if (AIController && bHasAim) 
    {
        const auto CombatInterface = Cast<IDGCombatInterface>(AIController->GetPawn());
        if (CombatInterface)
        {
            const auto AimActor = Cast<AActor>(Blackboard->GetValueAsObject(AimPawnKey.SelectedKeyName));
            CombatInterface->DoRangeAttack(AimActor);
        }
    }
}
