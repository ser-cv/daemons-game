// For Daemons and something else videogame purpose only

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
//#include "Perception/AISense_Sight.h"
//#include "Perception/AISense_Damage.h"
//#include "Perception/AISense_Team.h"
//#include "Perception/AISense_Hearing.h"
#include "DGCoreTypes.h"
#include "DGGetAimFromPerceptionsService.generated.h"

class UAISense;

UCLASS()
class DAEMONS_API UDGGetAimFromPerceptionsService : public UBTService
{
    GENERATED_BODY()

public:
    UDGGetAimFromPerceptionsService();

protected:
    //UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
    //TSubclassOf<UAISense> SenseToFilterBy;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
    TMap <EAIBehaviorState, TSubclassOf<UAISense>> SensesMap;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
    FBlackboardKeySelector BehaviorStateKey;

    //UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
    //TSubclassOf<UAISense> FirstLevelSense{UAISense_Damage::StaticClass()};

    //UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
    //TSubclassOf<UAISense> SecondLevelSense{UAISense_Sight::StaticClass()};

    //UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
    //TSubclassOf<UAISense> ThirdLevelSense{UAISense_Team::StaticClass()};

    //UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
    //TSubclassOf<UAISense> FourthLevelSense{UAISense_Hearing::StaticClass()};

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
    FBlackboardKeySelector AimActorKey;

public:
    virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;

private:
    EAIBehaviorState GainedState{EAIBehaviorState::No_Aim};

    AActor* GetClosestAim(AAIController* AIController);
    float GetDistanceBetween(AActor* Owner, AActor* PercievedActor);
};
