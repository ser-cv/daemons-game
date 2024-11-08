// For Daemons and something else videogame purpose only

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "DGBTTaskUpdateRouteDistance.generated.h"

UCLASS()
class DAEMONS_API UDGBTTaskUpdateRouteDistance : public UBTTaskNode
{
	GENERATED_BODY()

	UDGBTTaskUpdateRouteDistance();

protected:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	
};
