// For Daemons and something else videogame purpose only

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "DGBTTaskGetSoundSourceLocation.generated.h"


UCLASS()
class DAEMONS_API UDGBTTaskGetSoundSourceLocation : public UBTTaskNode
{
	GENERATED_BODY()

	UDGBTTaskGetSoundSourceLocation();

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
    FBlackboardKeySelector HeardAimKey;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
    FBlackboardKeySelector AimLocationKey;

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	
};
