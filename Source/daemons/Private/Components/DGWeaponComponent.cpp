// For Daemons and something else videogame purpose only

#include "Components/DGWeaponComponent.h"
#include "Weapons/DGBaseWeapon.h"
#include "DGCharacterBase.h"
#include "Weapons/DGBaseWeapon.h"

UDGWeaponComponent::UDGWeaponComponent()
{
    PrimaryComponentTick.bCanEverTick = true;
}

void UDGWeaponComponent::BeginPlay()
{
    Super::BeginPlay();

    OwnerCharacter = Cast<ADGCharacterBase>(GetOwner());
    TryToSwitchWeapon(0);
}

void UDGWeaponComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
    Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void UDGWeaponComponent::HandlePrimaryAttackInput() 
{
    if (bCanAttack == false || OwnerCharacter->GetActiveWeapon() == nullptr) return;

    OwnerCharacter->GetActiveWeapon()->StartFire();
}

void UDGWeaponComponent::StopPrimaryAttack() {}

void UDGWeaponComponent::HandleAlternativeModeInput() {}

void UDGWeaponComponent::StopAlternativeMode() {}

void UDGWeaponComponent::HandleReloadInput() {}

void UDGWeaponComponent::TryToSwitchWeapon(int SlotIndex) 
{
    if (bCanSwitch == false) return;
    if (SlotIndex >= WeaponClasses.Num()) return;
        
    GEngine->AddOnScreenDebugMessage(-1, 2, FColor::Green, FString::FromInt(SlotIndex));
    OwnerCharacter->SetWeaponChildActorClass(WeaponClasses[SlotIndex]);

    PreviousActiveWeaponSlot = ActiveWeaponSlot;
    ActiveWeaponSlot = SlotIndex;
}

void UDGWeaponComponent::HandleLastWeaponInput()
{
    TryToSwitchWeapon(PreviousActiveWeaponSlot);
}

void UDGWeaponComponent::HandleNextWeaponInput()
{
    if (ActiveWeaponSlot + 1 < WeaponClasses.Num())
    {
        TryToSwitchWeapon(ActiveWeaponSlot + 1);
    }
    else
    {
        TryToSwitchWeapon(0);
    }
}

void UDGWeaponComponent::HandlePreviousWeaponInput()
{
    if (ActiveWeaponSlot > 0)
    {
        TryToSwitchWeapon(ActiveWeaponSlot - 1);
    }
    else
    {
        TryToSwitchWeapon(WeaponClasses.Num() - 1);
    }
}

void UDGWeaponComponent::HandleSlotOneInput()
{
    TryToSwitchWeapon(0);
}

void UDGWeaponComponent::HandleSlotTwoInput()
{
    TryToSwitchWeapon(1);
}

void UDGWeaponComponent::HandleSlotThreeInput()
{
    TryToSwitchWeapon(2);
}

void UDGWeaponComponent::HandleSlotFourInput()
{
    TryToSwitchWeapon(3);
}

void UDGWeaponComponent::HandleSlotFiveInput()
{
    TryToSwitchWeapon(4);
}
