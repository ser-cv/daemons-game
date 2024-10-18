// For Daemons and something else videogame purpose only


#include "AI/EQS/DGSoundSourceLocEnvQueryContext.h"
#include "EnvironmentQuery/Items/EnvQueryItemType_Point.h"
#include "BehaviorTree/Blackboardcomponent.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "Perception/AIPerceptionComponent.h"

void UDGSoundSourceLocEnvQueryContext::ProvideContext(FEnvQueryInstance& QueryInstance, FEnvQueryContextData& ContextData) const 
{
    const auto ActorOwner = Cast<AActor>(QueryInstance.Owner.Get());
    if (!ActorOwner) return;
   
    const auto Blackboard = UAIBlueprintHelperLibrary::GetBlackboard(ActorOwner);
    if (!Blackboard) return;

    const FVector SoundSourceLocation = Blackboard->GetValueAsVector(AimLocationKeyName);
    UEnvQueryItemType_Point::SetContextHelper(ContextData, SoundSourceLocation);
}
