// For Daemons and something else videogame purpose only

#include "Components/DGWeaponComponent.h"
#include "Weapons/DGBaseWeapon.h"

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

void UDGWeaponComponent::InitWeapons()
{
    if (!CompToAttachWeapons.Get()) return;
    SpawnWeaponByType(MainWeaponClass, EItemType::MAIN_WEAPON);
    AttachWeaponToSocket(EItemType::MAIN_WEAPON, ArmedWeaponSocketName);
    ArmedWeaponType = EItemType::MAIN_WEAPON;
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
