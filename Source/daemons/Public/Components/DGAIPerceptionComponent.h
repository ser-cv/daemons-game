// For Daemons and something else videogame purpose only

#pragma once

#include "CoreMinimal.h"
#include "Perception/AIPerceptionComponent.h"
#include "DGAIPerceptionComponent.generated.h"


UCLASS()
class DAEMONS_API UDGAIPerceptionComponent : public UAIPerceptionComponent
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config")
	FName PlayerTagName{"Player"};

public:
	AActor* GetClosestEnemy() const;

};
