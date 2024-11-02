// For Daemons and something else videogame purpose only


#include "AI/DGMeeleAttackService.h"
#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Interfaces/DGCombatInterface.h"

UDGMeeleAttackService::UDGMeeleAttackService() 
{
    NodeName = "MeeleAttackService";
}

void UDGMeeleAttackService::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) 
{
    const auto AIController = OwnerComp.GetAIOwner();
    const auto Blackboard = OwnerComp.GetBlackboardComponent();

    if (AIController && Blackboard) 
    {
        const auto AimActor = Cast<AActor>(Blackboard->GetValueAsObject(AimPawnLocationKey.SelectedKeyName));
        const FVector AimLocation = AimActor ? AimActor->GetActorLocation() : FVector(); //Blackboard->GetValueAsVector(AimPawnLocationKey.SelectedKeyName);
        TryAttackAim(AIController, AimLocation);
    }
}

void UDGMeeleAttackService::TryAttackAim(AAIController* AIController, const FVector& AimLocation) 
{
    const auto AIPawn = AIController->GetPawn();
    if (!AIPawn) return;

    const float Distance = FVector::Distance(AimLocation, AIPawn->GetActorLocation());
    if (Distance > AttackDistance) return;

    const auto CombatInterface = Cast<IDGCombatInterface>(AIPawn);
    if (!CombatInterface) return;
    
    CombatInterface->DoLightMeeleAttack();
}
