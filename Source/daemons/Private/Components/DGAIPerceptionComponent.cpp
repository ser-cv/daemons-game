// For Daemons and something else videogame purpose only


#include "Components/DGAIPerceptionComponent.h"
#include "Perception/AISense_Sight.h"
#include "Perception/AISense_Hearing.h"
#include "AIController.h"
#include "Components/DGHealthComponent.h"

AActor* UDGAIPerceptionComponent::GetClosestEnemy() const
{
    TArray<AActor*> PercieveActors;
    GetCurrentlyPerceivedActors(UAISense_Sight::StaticClass(), PercieveActors);

    if (PercieveActors.Num() == 0)
    {
        GetCurrentlyPerceivedActors(UAISense_Hearing::StaticClass(), PercieveActors);
        
        if (PercieveActors.Num() == 0) return nullptr;
    }

    const auto Controller = Cast<AAIController>(GetOwner());
    if (!Controller) return nullptr;

    const auto Pawn = Controller->GetPawn();
    if (!Pawn) return nullptr;

    float BestDistance = MAX_FLT;
    AActor* BestPawn = nullptr;

    for (const auto& PercieveActor : PercieveActors)
    {
        const bool bIsPlayer = PercieveActor->ActorHasTag(PlayerTagName);
        const auto HealthComponent = PercieveActor->GetComponentByClass<UDGHealthComponent>();
        if (HealthComponent && HealthComponent->IsAlive() && bIsPlayer)
        {
            const auto CurrentDistance = (PercieveActor->GetActorLocation() - Pawn->GetActorLocation()).Size();
            if (CurrentDistance > BestDistance) continue; // <
            //{
            BestDistance = CurrentDistance;
            BestPawn = PercieveActor;
            //}
        }
    }

    return BestPawn;
}
