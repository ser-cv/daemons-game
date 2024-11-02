// For Daemons and something else videogame purpose only

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "DGBTTaskReportAboutEnemy.generated.h"


UCLASS()
class DAEMONS_API UDGBTTaskReportAboutEnemy : public UBTTaskNode
{
	GENERATED_BODY()
	
	UDGBTTaskReportAboutEnemy();

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
    FBlackboardKeySelector EnemyActorKey;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI", meta = (Clampmin = "100", Clampmax = "10000"))
    float ReportRange{1000.f};

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
};
