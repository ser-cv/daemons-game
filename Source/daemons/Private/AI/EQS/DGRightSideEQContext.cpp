// For Daemons and something else videogame purpose only


#include "AI/EQS/DGRightSideEQContext.h"
#include "EnvironmentQuery/EnvQueryTypes.h"
#include "EnvironmentQuery/Items/EnvQueryItemType_Point.h"
#include "BehaviorTree/Blackboardcomponent.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"

void UDGRightSideEQContext::ProvideContext(FEnvQueryInstance& QueryInstance, FEnvQueryContextData& ContextData) const 
{
    const auto ActorOwner = Cast<AActor>(QueryInstance.Owner.Get());
    if (!ActorOwner) return;

    const auto Blackboard = UAIBlueprintHelperLibrary::GetBlackboard(ActorOwner);
    if (!Blackboard) return;

    const auto ContextActor = Cast<AActor>(Blackboard->GetValueAsObject(AimKeyName));
    if (!ContextActor)
    {
        UE_LOG(LogTemp, Warning, TEXT("ContextActor not found"));
        return;
    }
    const FVector RightSideLocation = ContextActor->GetActorRightVector() * 1000.f;

    UEnvQueryItemType_Point::SetContextHelper(ContextData, RightSideLocation);
}
