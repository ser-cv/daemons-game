// For Daemons and something else videogame purpose only

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "DGWeaponComponent.generated.h"

class ADGBaseWeapon;

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class DAEMONS_API UDGWeaponComponent : public UActorComponent
{
    GENERATED_BODY()

public:
    UDGWeaponComponent();

protected:
    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
    TSubclassOf<ADGBaseWeapon> WeaponSpawnClass;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
    FName WeaponAttachSocketName{"WeaponAttachSocket"};

    virtual void BeginPlay() override;

public:
    virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

    void SetCompToAttachWeapons(USceneComponent* NewComp) { CompToAttachWeapons = NewComp; };
    void InitWeapons();

    void StartFire();
    void StopFire();

private:
    UPROPERTY()
    TObjectPtr<USceneComponent> CompToAttachWeapons;

    UPROPERTY()
    TObjectPtr<ADGBaseWeapon> WeaponInHands;
};
