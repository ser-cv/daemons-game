// For Daemons and something else videogame purpose only

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "DGAIController.generated.h"

class UDGAIPerceptionComponent;

UCLASS()
class DAEMONS_API ADGAIController : public AAIController
{
	GENERATED_BODY()

public:
	ADGAIController();
	
protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
    TObjectPtr<UDGAIPerceptionComponent> DGAIPerceptionComponent; 

	virtual void OnPossess(APawn* InPawn) override;
};
