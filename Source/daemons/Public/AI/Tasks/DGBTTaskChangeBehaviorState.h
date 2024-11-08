// For Daemons and something else videogame purpose only

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "DGCoreTypes.h"
#include "DGBTTaskChangeBehaviorState.generated.h"


UCLASS()
class DAEMONS_API UDGBTTaskChangeBehaviorState : public UBTTaskNode
{
	GENERATED_BODY()

public:
	UDGBTTaskChangeBehaviorState();

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
	EAIBehaviorState BehaviorState{EAIBehaviorState::No_Aim};

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
    FBlackboardKeySelector BehaviorStateKey;

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	
};
