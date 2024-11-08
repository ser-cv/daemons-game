// For Daemons and something else videogame purpose only

#include "UsableActors/DGPatrolRoute.h"
#include "Components/SplineComponent.h"

ADGPatrolRoute::ADGPatrolRoute()
{
    PrimaryActorTick.bCanEverTick = false;
    Spline = CreateDefaultSubobject<USplineComponent>("SplineComponent");
    SetRootComponent(Spline);
}

void ADGPatrolRoute::BeginPlay()
{
    Super::BeginPlay();
}

float ADGPatrolRoute::GetPatrolRouteLenght() const
{
    check(Spline);
    return Spline->GetSplineLength();
}

FVector ADGPatrolRoute::GetPatrolRouteLocationAtDistance(float Distance) const
{
    check(Spline);
    return Spline->GetLocationAtDistanceAlongSpline(Distance, ESplineCoordinateSpace::World);
}

float ADGPatrolRoute::GetDistanceClosestToLocation(const FVector& PawnLocation) const
{
    check(Spline);
    const float InputKey = Spline->FindInputKeyClosestToWorldLocation(PawnLocation);
    return Spline->GetDistanceAlongSplineAtSplineInputKey(InputKey);
}

float ADGPatrolRoute::GetPartOfPatrolRouteLenght() const
{
    check(Spline);
    return Spline->GetSplineLength() / PatrolRouteParts;
}
