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
    if (!WeaponSpawnClass || !CompToAttachWeapons.Get()) return;
    WeaponInHands = GetWorld()->SpawnActor<ADGBaseWeapon>(WeaponSpawnClass);

    if (!WeaponInHands.Get()) return;

    FAttachmentTransformRules AttachmentRules(EAttachmentRule::SnapToTarget, false);
    WeaponInHands->AttachToComponent(CompToAttachWeapons, AttachmentRules, WeaponAttachSocketName);

    WeaponInHands->SetOwner(GetOwner());
}

void UDGWeaponComponent::StartFire()
{
    if (!WeaponInHands.Get()) return;
    WeaponInHands->StartFire();
}

void UDGWeaponComponent::StopFire() {}
