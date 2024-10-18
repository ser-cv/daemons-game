// For Daemons and something else videogame purpose only

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "DGBTTaskForgetSoundSource.generated.h"


UCLASS()
class DAEMONS_API UDGBTTaskForgetSoundSource : public UBTTaskNode
{
	GENERATED_BODY()
	
	UDGBTTaskForgetSoundSource();

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
    FBlackboardKeySelector HeardAimKey;

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
};
