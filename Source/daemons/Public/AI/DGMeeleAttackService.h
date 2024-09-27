// For Daemons and something else videogame purpose only

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "DGMeeleAttackService.generated.h"

/**
 * 
 */
UCLASS()
class DAEMONS_API UDGMeeleAttackService : public UBTService
{
	GENERATED_BODY()
	
public:
	UDGMeeleAttackService();
	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
	float AttackDistance{200.f};

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
    FBlackboardKeySelector AimPawnLocationKey;

private:
	void TryAttackAim(AAIController* AIController, const FVector& AimLocation);
};
