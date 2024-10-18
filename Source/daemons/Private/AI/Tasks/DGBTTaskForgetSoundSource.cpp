// For Daemons and something else videogame purpose only


#include "AI/Tasks/DGBTTaskForgetSoundSource.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AIController.h"
#include "Perception/AIPerceptionComponent.h"

UDGBTTaskForgetSoundSource::UDGBTTaskForgetSoundSource() 
{
    NodeName = "Forget Sound Source";
    HeardAimKey.AddObjectFilter(this, "Pawns", APawn::StaticClass());
}

EBTNodeResult::Type UDGBTTaskForgetSoundSource::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
    const auto AIController = OwnerComp.GetAIOwner();
    if (!AIController) return EBTNodeResult::Failed;

    const auto Blackboard = OwnerComp.GetBlackboardComponent();
    if (!Blackboard) return EBTNodeResult::Failed;

    const auto HearedActor = Cast<AActor>(Blackboard->GetValueAsObject(HeardAimKey.SelectedKeyName));
    const auto PerceptionComponent = AIController->PerceptionComponent;
    if (!PerceptionComponent) return EBTNodeResult::Failed;

    PerceptionComponent->ForgetActor(HearedActor);
    Blackboard->SetValueAsObject(HeardAimKey.SelectedKeyName, nullptr);
    return EBTNodeResult::Succeeded;
}
