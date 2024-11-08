// For Daemons and something else videogame purpose only

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "DGBTTaskFindPatrolRoute.generated.h"

UCLASS()
class DAEMONS_API UDGBTTaskFindPatrolRoute : public UBTTaskNode
{
	GENERATED_BODY()

	UDGBTTaskFindPatrolRoute();

protected:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
};
