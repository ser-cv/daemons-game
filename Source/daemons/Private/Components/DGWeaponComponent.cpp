// For Daemons and something else videogame purpose only

#include "Components/DGWeaponComponent.h"
#include "Weapons/DGBaseWeapon.h"
#include "DGCharacterBase.h"

UDGWeaponComponent::UDGWeaponComponent()
{
    PrimaryComponentTick.bCanEverTick = true;
}

void UDGWeaponComponent::BeginPlay()
{
    Super::BeginPlay();
}

void UDGWeaponComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
    Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void UDGWeaponComponent::HandlePrimaryAttackInput() {}

void UDGWeaponComponent::HandleAlternativeModeInput() {}

void UDGWeaponComponent::TryToSwitchWeapon(int SlotIndex) 
{
    if (CanSwitch == false) return;
    if (SlotIndex >= WeaponClasses.Num()) return;
        
    GEngine->AddOnScreenDebugMessage(-1, 2, FColor::Green, FString::FromInt(SlotIndex));
    //Cast<ADGCharacterBase>(GetOwner())->SetWeaponChildActorClass(WeaponClasses[SlotIndex]);

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

void UDGWeaponComponent::SpawnWeaponByType(UClass* WeaponClass, EItemType WeaponType)
{
    if (!WeaponClass || !GetWorld()) return;
    WearableWeapons.Add(WeaponType, GetWorld()->SpawnActor<ADGBaseWeapon>(WeaponClass));
    if (!WearableWeapons.FindRef(WeaponType)) return;
    WearableWeapons[WeaponType]->SetOwner(GetOwner());
}

void UDGWeaponComponent::AttachWeaponToSocket(EItemType WeaponType, FName AttachingSocketName)
{
    if (!WearableWeapons.FindRef(WeaponType)) return;
    FAttachmentTransformRules AttachmentRules(EAttachmentRule::SnapToTarget, false);
    WearableWeapons[WeaponType]->AttachToComponent(CompToAttachWeapons, AttachmentRules, AttachingSocketName);
}
