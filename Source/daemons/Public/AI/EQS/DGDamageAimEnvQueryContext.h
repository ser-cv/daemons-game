// For Daemons and something else videogame purpose only

#pragma once

#include "CoreMinimal.h"
#include "EnvironmentQuery/EnvQueryContext.h"
#include "DGDamageAimEnvQueryContext.generated.h"


UCLASS()
class DAEMONS_API UDGDamageAimEnvQueryContext : public UEnvQueryContext
{
	GENERATED_BODY()
	
public:
	virtual void ProvideContext(FEnvQueryInstance& QueryInstance, FEnvQueryContextData& ContextData) const override;

protected:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
    FName AimKeyName{"CausingDamageAim"};
};
