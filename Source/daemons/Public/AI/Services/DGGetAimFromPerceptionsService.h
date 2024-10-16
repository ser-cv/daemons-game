// For Daemons and something else videogame purpose only

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "DGGetAimFromPerceptionsService.generated.h"

class UAISense;

UCLASS()
class DAEMONS_API UDGGetAimFromPerceptionsService : public UBTService
{
    GENERATED_BODY()

public:
    UDGGetAimFromPerceptionsService();

protected:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
    TSubclassOf<UAISense> SenseToFilterBy;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
    FBlackboardKeySelector AimActorKey;

public:
    virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;

private:
    AActor* GetClosestAim(AAIController* AIController);
    float GetDistanceBetween(AActor* Owner, AActor* PercievedActor);
};
