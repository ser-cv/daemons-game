// For Daemons and something else videogame purpose only

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "DGCoreTypes.h"
#include "DGWeaponComponent.generated.h"

class ADGBaseWeapon;
class ADGCharacterBase;

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

    // Handle input methods

    void HandlePrimaryAttackInput();
    void StopPrimaryAttack();

    void HandleAlternativeModeInput();
    void StopAlternativeMode();

    void HandleReloadInput();

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

    bool bCanSwitch{true};

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "WeaponComponent")
    int ActiveWeaponSlot{0};

    int PreviousActiveWeaponSlot{0};

private:
    UPROPERTY()
    TObjectPtr<USceneComponent> CompToAttachWeapons;

    bool bCanAttack{true};

    UPROPERTY()
    TObjectPtr<ADGCharacterBase> OwnerCharacter;
};
