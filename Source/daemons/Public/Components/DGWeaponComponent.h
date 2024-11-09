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
    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "ForTesting")
    TSubclassOf<ADGBaseWeapon> MainWeaponClass;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
    FName ArmedWeaponSocketName{"ArmedWeaponSocket"};

    virtual void BeginPlay() override;

public:
    virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

    void SetCompToAttachWeapons(USceneComponent* NewComp) { CompToAttachWeapons = NewComp; };
    void InitWeapons();

    void TryToSwitchWeapon(int SlotIndex);

    // Weapons switching

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

    EItemType ArmedWeaponType{EItemType::MAIN_WEAPON};

    void SpawnWeaponByType(UClass* WeaponClass, EItemType WeaponType);
    void AttachWeaponToSocket(EItemType WeaponType, FName AttachingSocketName);
};
