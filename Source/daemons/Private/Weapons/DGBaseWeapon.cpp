// For Daemons and something else videogame purpose only

#include "Weapons/DGBaseWeapon.h"
#include "DrawDebugHelpers.h"

ADGBaseWeapon::ADGBaseWeapon()
{
    PrimaryActorTick.bCanEverTick = true;

    WeaponRootComponent = CreateDefaultSubobject<USceneComponent>("WeaponRootComponent");
    SetRootComponent(WeaponRootComponent);

    WeaponMesh = CreateDefaultSubobject<UStaticMeshComponent>("WeaponMesh");
    WeaponMesh->SetupAttachment(RootComponent);
}

void ADGBaseWeapon::BeginPlay()
{
    Super::BeginPlay();

    check(WeaponMesh);
}

void ADGBaseWeapon::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
}

void ADGBaseWeapon::StartFire()
{
    MakeShot();
}

void ADGBaseWeapon::StopFire() {}

void ADGBaseWeapon::MakeShot()
{
    if (AmmoUnits <= 0) return;

    const FVector MuzzleLocation = WeaponMesh->GetSocketLocation(MuzzleSocketName);

    FVector ViewLocation{FVector::ZeroVector};
    FRotator ViewRotation{FRotator::ZeroRotator};
    if (!GetPlayerViewPoint(ViewLocation, ViewRotation)) return;

    const auto BulletSpread = 5.f;
    const auto HalfRad = FMath::DegreesToRadians(BulletSpread);
    const FVector ShootDirection = FMath::VRandCone(ViewRotation.Vector(), HalfRad);

    const float Distance = 1500.f;
    const FVector LineEnd = MuzzleLocation + ShootDirection * Distance;

    //--AmmoUnits;

    DrawDebugLine(GetWorld(), MuzzleLocation, LineEnd, FColor::Green, false, 2.f, 0u, 2.f);
}

bool ADGBaseWeapon::GetPlayerViewPoint(FVector& ViewLocation, FRotator& ViewRotation)
{
    const auto PlayerController = GetPlayerController();
    if (!PlayerController) return false;
    PlayerController->GetPlayerViewPoint(ViewLocation, ViewRotation);
    return true;
}

APlayerController* ADGBaseWeapon::GetPlayerController()
{
    const auto OwnerPawn = Cast<APawn>(GetOwner());
    if (!OwnerPawn) return nullptr;
    return Cast<APlayerController>(OwnerPawn->GetController());
}
