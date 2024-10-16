// For Daemons and something else videogame purpose only


#include "AI/Services/DGGetAimFromPerceptionsService.h"
#include "AIController.h"
#include "Perception/AIPerceptionComponent.h"
#include "BehaviorTree/BlackboardComponent.h"

UDGGetAimFromPerceptionsService::UDGGetAimFromPerceptionsService() 
{
    NodeName = "Get Aim From Perception Service";
}

void UDGGetAimFromPerceptionsService::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
    const auto AIController = OwnerComp.GetAIOwner();
    AActor* AimActor = GetClosestAim(AIController);
    const auto Blackboard = OwnerComp.GetBlackboardComponent();
    if (Blackboard)
    {
        Blackboard->SetValueAsObject(AimActorKey.SelectedKeyName, AimActor);
    }

    Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);
}

AActor* UDGGetAimFromPerceptionsService::GetClosestAim(AAIController* AIController)
{
    if (!AIController) return nullptr;
    TArray<AActor*> PercievedActors;
    //AIController->GetPerceptionComponent()->GetHostileActorsBySense(SenseToFilterBy, PercievedActors);
    AIController->GetPerceptionComponent()->GetPerceivedHostileActorsBySense(SenseToFilterBy, PercievedActors);
    if (!PercievedActors.Num()) return nullptr;
    float BestDistance = MAX_FLT;
    AActor* AimActor = nullptr;
    for (const auto PercievedActor : PercievedActors)
    {
        const float DistanceBeetween = GetDistanceBetween(AIController->GetPawn(), PercievedActor);
        if (DistanceBeetween > BestDistance) continue;
        BestDistance = DistanceBeetween;
        AimActor = PercievedActor;
    }
    return AimActor;
}

float UDGGetAimFromPerceptionsService::GetDistanceBetween(AActor* Owner, AActor* PercievedActor)
{
    if (!Owner || !PercievedActor) return MAX_FLT;
    return (PercievedActor->GetActorLocation() - Owner->GetActorLocation()).Size();
}
