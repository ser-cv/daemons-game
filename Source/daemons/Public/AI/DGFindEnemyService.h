// For Daemons and something else videogame purpose only

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "DGFindEnemyService.generated.h"


UCLASS()
class DAEMONS_API UDGFindEnemyService : public UBTService
{
	GENERATED_BODY()

public:
	UDGFindEnemyService();

	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
    FBlackboardKeySelector AimPawnLocationKey;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
    FBlackboardKeySelector AimPawnKey;
};
