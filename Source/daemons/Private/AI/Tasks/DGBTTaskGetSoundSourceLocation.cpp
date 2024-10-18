// For Daemons and something else videogame purpose only


#include "AI/Tasks/DGBTTaskGetSoundSourceLocation.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AIController.h"
#include "Perception/AIPerceptionComponent.h"

UDGBTTaskGetSoundSourceLocation::UDGBTTaskGetSoundSourceLocation() 
{
    NodeName = "Get Sound Source Location";
    AimLocationKey.AddVectorFilter(this, "Aim Location");
}

EBTNodeResult::Type UDGBTTaskGetSoundSourceLocation::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
    const auto AIController = OwnerComp.GetAIOwner();
    if (!AIController) return EBTNodeResult::Failed;

    const auto Blackboard = OwnerComp.GetBlackboardComponent();
    if (!Blackboard) return EBTNodeResult::Failed;

    const auto HearedActor = Cast<AActor>(Blackboard->GetValueAsObject(HeardAimKey.SelectedKeyName));
    const auto PerceptionComponent = AIController->PerceptionComponent;
    if (!PerceptionComponent) return EBTNodeResult::Failed;

    const auto ActorInfo = PerceptionComponent->GetActorInfo(*HearedActor);
    if (!ActorInfo) return EBTNodeResult::Failed;
    const FVector SoundSourceLocation = ActorInfo->GetLastStimulusLocation();
    Blackboard->SetValueAsVector(AimLocationKey.SelectedKeyName, SoundSourceLocation);
    return EBTNodeResult::Succeeded;
}
