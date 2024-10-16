// For Daemons and something else videogame purpose only


#include "AI/EQS/DGAimEnvQueryContext.h"

#include "EnvironmentQuery/EnvQueryTypes.h"
#include "EnvironmentQuery/Items/EnvQueryItemType_Actor.h"
#include "BehaviorTree/Blackboardcomponent.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"

void UDGAimEnvQueryContext::ProvideContext(FEnvQueryInstance& QueryInstance, FEnvQueryContextData& ContextData) const 
{
    const auto ActorOwner = Cast<AActor>(QueryInstance.Owner.Get());
    if (!ActorOwner) return;

    const auto Blackboard = UAIBlueprintHelperLibrary::GetBlackboard(ActorOwner);
    if (!Blackboard) return;

    const auto ContextObject = Blackboard->GetValueAsObject(AimKeyName);

    UEnvQueryItemType_Actor::SetContextHelper(ContextData, Cast<AActor>(ContextObject));
}
