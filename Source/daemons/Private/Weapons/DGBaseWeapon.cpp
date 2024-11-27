// For Daemons and something else videogame purpose only

#include "Weapons/DGBaseWeapon.h"
#include "Engine/DamageEvents.h"
#include "DrawDebugHelpers.h"
#include "Kismet/GameplayStatics.h"

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

    if (GetWorld())
    {
        PlayerController = UGameplayStatics::GetPlayerController(this, 0);
    }
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

    // Delay between shots
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
    GEngine->AddOnScreenDebugMessage(-1, 1, FColor::Red, "BOO");

    const FVector MuzzleLocation = WeaponMesh->GetSocketLocation(MuzzleSocketName);

    FVector ViewLocation{FVector::ZeroVector};
    FRotator ViewRotation{FRotator::ZeroRotator};
    if (GetPlayerViewPoint(ViewLocation, ViewRotation) == false) return;

    const float BulletSpread = 5.f;
    const float HalfRad = FMath::DegreesToRadians(BulletSpread);
    const FVector ShootDirection = ViewRotation.Vector();  //= FMath::VRandCone(ViewRotation.Vector(), HalfRad);
    const FVector LineEnd = ViewLocation + ShootDirection * ShotLineTraceDistance;

    FHitResult Hit;
    MakeHit(Hit, ViewLocation, LineEnd);

    if (Hit.bBlockingHit)
    {
        MakeDamage(Hit);
    }

    UpdateAmmo(-1);

    GEngine->AddOnScreenDebugMessage(-1, 1, FColor::Red, LineEnd.ToString());
    DrawDebugLine(GetWorld(), MuzzleLocation, LineEnd, FColor::Green, false, 2.f, 0u, 2.f);
}

bool ADGBaseWeapon::GetPlayerViewPoint(FVector& ViewLocation, FRotator& ViewRotation)
{
    if (!PlayerController)
    {
        GEngine->AddOnScreenDebugMessage(-1, 1, FColor::Red, "Hail2U");

        return false;
    }

    PlayerController->GetPlayerViewPoint(ViewLocation, ViewRotation);
    return true;
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
    AActor* const DamagedActor = Hit.GetActor();
    if (!DamagedActor) return;
    DamagedActor->TakeDamage(DamageAmount, FDamageEvent(), PlayerController, this);
}

void ADGBaseWeapon::UpdateAmmo(int32 Amount)
{
    AmmoInClip = FMath::Clamp(AmmoInClip + Amount, 0, ClipCapacity);
    bIsCharged = false;
}

void ADGBaseWeapon::ReloadWeapon()
{
    const int32 AmmoToLoad = (Ammo / ClipCapacity) ? ClipCapacity : Ammo;
    UpdateAmmo(AmmoToLoad);
    Ammo = bIsInfiniteAmmo ? MaxAmmo : Ammo - AmmoInClip;
    bIsCharged = true;

    UE_LOG(LogTemp, Display, TEXT("Ammo in clip: %i, the remaining ammo: %i"), AmmoInClip, Ammo)
}
