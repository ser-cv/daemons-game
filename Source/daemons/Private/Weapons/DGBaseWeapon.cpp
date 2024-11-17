// For Daemons and something else videogame purpose only

#include "Weapons/DGBaseWeapon.h"
#include "Engine/DamageEvents.h"
#include "DrawDebugHelpers.h"

ADGBaseWeapon::ADGBaseWeapon()
{
    PrimaryActorTick.bCanEverTick = true;

    WeaponRootComponent = CreateDefaultSubobject<USceneComponent>("WeaponRootComponent");
    SetRootComponent(WeaponRootComponent);

    WeaponMesh = CreateDefaultSubobject<UStaticMeshComponent>("WeaponMesh");
    WeaponMesh->SetupAttachment(RootComponent);

    WeaponMesh->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECR_Ignore);
    WeaponMesh->SetCastShadow(false);
}

void ADGBaseWeapon::BeginPlay()
{
    Super::BeginPlay();

    check(WeaponMesh);

    Ammo = MaxAmmo;
    AmmoInClip = ClipCapacity;
    bIsCharged = true;
}

void ADGBaseWeapon::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
}

void ADGBaseWeapon::SetOwner(AActor* NewOwner)
{
    Super::SetOwner(NewOwner);
    OwnerPawn = Cast<APawn>(NewOwner);
}

void ADGBaseWeapon::StartFire()
{
    if (IsEmptyClip() || !bIsCharged || bIsReloading) return;

    MakeShot();
    bIsTriggerPressed = true;

    if (GetWorldTimerManager().IsTimerActive(ChargingTimerHandle)) return;
    GetWorldTimerManager().SetTimer(
        ChargingTimerHandle,
        [&]()
        {
            bIsCharged = true;
            (bIsTriggerPressed && bIsAutomatic && !IsEmptyClip()) ? MakeShot() : GetWorldTimerManager().ClearTimer(ChargingTimerHandle);
        },
        60.f / ShotsPerMinute, true);
}

void ADGBaseWeapon::StopFire()
{
    bIsTriggerPressed = false;
}

void ADGBaseWeapon::StartReloading()
{
    if (bIsReloading || !Ammo || bIsTriggerPressed) return;
    bIsReloading = true;

    GetWorldTimerManager().SetTimer(
        RealoadingTimerHandle,
        [&]()
        {
            bIsReloading = false;
            ReloadWeapon();
        },
        ReloadingTime, false);
}

void ADGBaseWeapon::MakeShot()
{
    const FVector MuzzleLocation = WeaponMesh->GetSocketLocation(MuzzleSocketName);

    FVector ViewLocation{FVector::ZeroVector};
    FRotator ViewRotation{FRotator::ZeroRotator};
    if (!GetPlayerViewPoint(ViewLocation, ViewRotation)) return;

    const auto BulletSpread = 5.f;
    const auto HalfRad = FMath::DegreesToRadians(BulletSpread);
    const FVector ShootDirection = FMath::VRandCone(ViewRotation.Vector(), HalfRad);
    const FVector LineEnd = MuzzleLocation + ShootDirection * LineTraceDistance;

    FHitResult Hit;
    MakeHit(Hit, MuzzleLocation, LineEnd);

    if (Hit.bBlockingHit)
    {
        MakeDamage(Hit);
    }

    ChangeAmmo(-1);

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
    if (!OwnerPawn) return nullptr;
    return Cast<APlayerController>(OwnerPawn->GetController());
}

void ADGBaseWeapon::MakeHit(FHitResult& Hit, const FVector& TraceStart, const FVector& TraceEnd)
{
    if (!GetWorld()) return;
    FCollisionQueryParams QueryParams;
    TArray<AActor*> IgnoredActors = {GetOwner(), this};
    QueryParams.AddIgnoredActors(IgnoredActors);

    GetWorld()->LineTraceSingleByChannel(Hit, TraceStart, TraceEnd, ECollisionChannel::ECC_Visibility, QueryParams);
}

void ADGBaseWeapon::MakeDamage(const FHitResult& Hit)
{
    const auto DamagedActor = Hit.GetActor();
    if (!DamagedActor) return;
    DamagedActor->TakeDamage(DamageAmount, FDamageEvent(), GetPlayerController(), this);
}

void ADGBaseWeapon::ChangeAmmo(int32 Amount)
{
    AmmoInClip = FMath::Clamp(AmmoInClip + Amount, 0, ClipCapacity);
    bIsCharged = false;
}

void ADGBaseWeapon::ReloadWeapon()
{
    const int32 AmmoToLoad = (Ammo / ClipCapacity) ? ClipCapacity : Ammo;
    ChangeAmmo(AmmoToLoad);
    Ammo = bIsInfiniteAmmo ? MaxAmmo : Ammo - AmmoInClip;
    bIsCharged = true;

    UE_LOG(LogTemp, Display, TEXT("Ammo in clip: %i, the remaining ammo: %i"), AmmoInClip, Ammo)
}
