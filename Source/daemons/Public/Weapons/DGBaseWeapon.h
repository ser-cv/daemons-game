// For Daemons and something else videogame purpose only

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DGBaseWeapon.generated.h"

UCLASS()
class DAEMONS_API ADGBaseWeapon : public AActor
{
    GENERATED_BODY()

public:
    ADGBaseWeapon();

protected:
    UPROPERTY(VisibleDefaultsOnly)
    TObjectPtr<USceneComponent> WeaponRootComponent;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
    TObjectPtr<UStaticMeshComponent> WeaponMesh;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
    FName MuzzleSocketName{"MuzzleSocket"};

    virtual void BeginPlay() override;

public:
    virtual void Tick(float DeltaTime) override;

    void StartFire();
    void StopFire();

private:
    int32 AmmoUnits{10};

    void MakeShot();
    bool GetPlayerViewPoint(FVector& ViewLocation, FRotator& ViewRotation);
    APlayerController* GetPlayerController();
};
