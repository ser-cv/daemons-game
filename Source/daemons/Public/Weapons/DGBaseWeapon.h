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

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config", meta = (ClampMin = "1", ClampMax = "4000"))
    float LineTraceDistance{1500.f};

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config", meta = (ClampMin = "0", ClampMax = "100"))
    float DamageAmount{10.f};

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Config")
    FName MuzzleSocketName{"MuzzleSocket"};

    virtual void BeginPlay() override;

public:
    virtual void Tick(float DeltaTime) override;
    virtual void SetOwner(AActor* NewOwner) override;

    void StartFire();
    void StopFire();

private:
    UPROPERTY()
    TObjectPtr<APawn> OwnerPawn;

    int32 AmmoUnits{10};

    void MakeShot();
    bool GetPlayerViewPoint(FVector& ViewLocation, FRotator& ViewRotation);
    APlayerController* GetPlayerController();
    void MakeHit(FHitResult& Hit, const FVector& TraceStart, const FVector& TraceEnd);
    void MakeDamage(const FHitResult& Hit);
};
