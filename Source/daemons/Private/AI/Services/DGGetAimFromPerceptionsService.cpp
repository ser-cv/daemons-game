// For Daemons and something else videogame purpose only


#include "AI/Services/DGGetAimFromPerceptionsService.h"
#include "AIController.h"
#include "Perception/AIPerceptionComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Perception/AISense_Sight.h"
#include "Perception/AISense_Damage.h"
#include "Perception/AISense_Team.h"
#include "Perception/AISense_Hearing.h"

UDGGetAimFromPerceptionsService::UDGGetAimFromPerceptionsService() 
{
    NodeName = "Get Aim From Perception Service";

    BehaviorStateKey.AddEnumFilter(this, "AIBehaviorState", StaticEnum<EAIBehaviorState>());

    SensesMap.Add(EAIBehaviorState::Damage_Received, UAISense_Damage::StaticClass());
    SensesMap.Add(EAIBehaviorState::Sight_Detected, UAISense_Sight::StaticClass());
    SensesMap.Add(EAIBehaviorState::Team_Reported, UAISense_Team::StaticClass());
    SensesMap.Add(EAIBehaviorState::Hearing_Detected, UAISense_Hearing::StaticClass());
}

void UDGGetAimFromPerceptionsService::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
    const auto AIController = OwnerComp.GetAIOwner();
    AActor* AimActor = GetClosestAim(AIController);
    const auto Blackboard = OwnerComp.GetBlackboardComponent();
    if (Blackboard)
    {
        Blackboard->SetValueAsObject(AimActorKey.SelectedKeyName, AimActor);
        
        if (AimActor)
        {
            Blackboard->SetValueAsEnum(BehaviorStateKey.SelectedKeyName, (uint8)GainedState);
        }
    }

    Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);
}

AActor* UDGGetAimFromPerceptionsService::GetClosestAim(AAIController* AIController)
{
    if (!AIController) return nullptr;
    TArray<AActor*> PercievedActors;
    
    for (TPair<EAIBehaviorState, TSubclassOf<UAISense>> Sense : SensesMap)
    {
        AIController->GetPerceptionComponent()->GetPerceivedHostileActorsBySense(Sense.Value, PercievedActors);
        if (!PercievedActors.Num()) continue;
        GainedState = Sense.Key;
        break;
    }

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
