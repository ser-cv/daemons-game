// For Daemons and something else videogame purpose only

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DGPatrolRoute.generated.h"

class USplineComponent;

UCLASS()
class DAEMONS_API ADGPatrolRoute : public AActor
{
    GENERATED_BODY()

public:
    ADGPatrolRoute();

protected:
    UPROPERTY(EditDefaultsOnly, Category = "Spline", meta = (AllowPrivateAccess = true))
    TObjectPtr<USplineComponent> Spline;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Patrol", meta = (Clampmin = "10", clampmax = "100"))
    int32 PatrolRouteParts{20};

    virtual void BeginPlay() override;

public:
    float GetDistanceClosestToLocation(const FVector& PawnLocation) const;
    float GetPartOfPatrolRouteLenght() const;
    float GetPatrolRouteLenght() const;

    FVector GetPatrolRouteLocationAtDistance(float Distance) const;
};
