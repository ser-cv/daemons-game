// For Daemons and something else videogame purpose only

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "DGBTTaskGetRouteLocation.generated.h"

UCLASS()
class DAEMONS_API UDGBTTaskGetRouteLocation : public UBTTaskNode
{
	GENERATED_BODY()

	UDGBTTaskGetRouteLocation();

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
    FBlackboardKeySelector PatrolRouteLocationKey;

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
};
