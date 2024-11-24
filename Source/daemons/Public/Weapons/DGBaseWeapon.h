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

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config")
    bool bIsAutomatic{false};

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config")
    bool bIsInfiniteAmmo{false};

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config", meta = (EditCondition = "bIsAutomatic", ClampMin = "1", ClampMax = "1000"))
    int32 ShotsPerMinute{400};

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Config", meta = (ClampMin = "0", ClampMax = "1000"))
    int32 MaxAmmo{200};

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Config", meta = (ClampMin = "0", ClampMax = "100"))
    int32 ClipCapacity{20};

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Config", meta = (ClampMin = "0", ClampMax = "100"))
    float ReloadingTime{3.f};

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Config")
    FName MuzzleSocketName{"MuzzleSocket"};

    virtual void BeginPlay() override;

public:
    virtual void Tick(float DeltaTime) override;
    virtual void SetOwner(AActor* NewOwner) override;

    virtual void StartFire();
    void StopFire();

    void StartReloading();

private:
    UPROPERTY()
    TObjectPtr<APawn> OwnerPawn;

    int32 AmmoUnits{10};
    int32 Ammo{};
    int32 AmmoInClip{};

    bool bIsCharged{false};
    bool bIsTriggerPressed{false};

    FTimerHandle ChargingTimerHandle;
    FTimerHandle RealoadingTimerHandle;

    bool bIsReloading{false};

    void MakeShot();
    bool GetPlayerViewPoint(FVector& ViewLocation, FRotator& ViewRotation);
    APlayerController* PlayerController;
    void MakeHit(FHitResult& Hit, const FVector& TraceStart, const FVector& TraceEnd);
    void MakeDamage(const FHitResult& Hit);
    bool IsEmptyClip() const { return !AmmoInClip; };
    void UpdateAmmo(int32 Amount);
    void ReloadWeapon();
};
