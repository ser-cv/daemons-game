// For Daemons and something else videogame purpose only


#include "AI/Tasks/DGBTTaskChangeBehaviorState.h"
#include "BehaviorTree/BlackboardComponent.h"

UDGBTTaskChangeBehaviorState::UDGBTTaskChangeBehaviorState() 
{
    NodeName = "Change AI Behavior State";
    BehaviorStateKey.AddEnumFilter(this, "AIBehaviorState", StaticEnum<EAIBehaviorState>());
}

EBTNodeResult::Type UDGBTTaskChangeBehaviorState::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
    const auto Blackboard = OwnerComp.GetBlackboardComponent();
    if (!Blackboard) return EBTNodeResult::Failed;

    Blackboard->SetValueAsEnum(BehaviorStateKey.SelectedKeyName, (uint8)BehaviorState);
    return EBTNodeResult::Succeeded;
}
