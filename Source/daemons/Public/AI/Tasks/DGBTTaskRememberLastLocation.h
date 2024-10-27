// For Daemons and something else videogame purpose only

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "DGBTTaskRememberLastLocation.generated.h"

UCLASS()
class DAEMONS_API UDGBTTaskRememberLastLocation : public UBTTaskNode
{
	GENERATED_BODY()

	UDGBTTaskRememberLastLocation();

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
    FBlackboardKeySelector InstigatorKey;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
    FBlackboardKeySelector LastSeenLocationKey;

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
};
