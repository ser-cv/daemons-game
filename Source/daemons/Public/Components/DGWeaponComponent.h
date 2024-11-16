// For Daemons and something else videogame purpose only

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "DGCoreTypes.h"
#include "DGWeaponComponent.generated.h"

class ADGBaseWeapon;

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class DAEMONS_API UDGWeaponComponent : public UActorComponent
{
    GENERATED_BODY()

public:
    UDGWeaponComponent();

protected:
    // Weapon classes
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "WeaponComponent")
    TArray<TSubclassOf<ADGBaseWeapon>> WeaponClasses;

    virtual void BeginPlay() override;

public:
    virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

    void SetCompToAttachWeapons(USceneComponent* NewComp) { CompToAttachWeapons = NewComp; };

    void HandlePrimaryAttackInput();
    void HandleAlternativeModeInput();

    // Weapons switching
    void TryToSwitchWeapon(int SlotIndex);

    void HandleLastWeaponInput();
    void HandleNextWeaponInput();
    void HandlePreviousWeaponInput();
    void HandleSlotOneInput();
    void HandleSlotTwoInput();
    void HandleSlotThreeInput();
    void HandleSlotFourInput();
    void HandleSlotFiveInput();

    bool CanSwitch{true};

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "WeaponComponent")
    int ActiveWeaponSlot{0};

    int PreviousActiveWeaponSlot{0};

private:
    UPROPERTY()
    TObjectPtr<USceneComponent> CompToAttachWeapons;

    UPROPERTY()
    TMap<EItemType, ADGBaseWeapon*> WearableWeapons;

    UPROPERTY()
    TObjectPtr<ADGBaseWeapon> ActiveWeapon;

    EItemType ArmedWeaponType{EItemType::MAIN_WEAPON};

    void SpawnWeaponByType(UClass* WeaponClass, EItemType WeaponType);
    void AttachWeaponToSocket(EItemType WeaponType, FName AttachingSocketName);
};
