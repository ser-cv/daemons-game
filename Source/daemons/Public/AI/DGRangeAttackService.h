// For Daemons and something else videogame purpose only

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "DGRangeAttackService.generated.h"

UCLASS()
class DAEMONS_API UDGRangeAttackService : public UBTService
{
	GENERATED_BODY()

public:
	UDGRangeAttackService();

	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
	
protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
    FBlackboardKeySelector AimPawnKey;
};
