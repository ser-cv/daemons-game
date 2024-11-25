// For Daemons and something else videogame purpose only

#include "Components/DGHealthComponent.h"
#include "Game/DGGameModeBase.h"

UDGHealthComponent::UDGHealthComponent()
{
    PrimaryComponentTick.bCanEverTick = true;
}

void UDGHealthComponent::BeginPlay()
{
    Super::BeginPlay();

    SetHealth(MaxHealth);

    AActor* ComponentOwner = GetOwner();
    if (ComponentOwner)
    {
        ComponentOwner->OnTakeAnyDamage.AddDynamic(this, &UDGHealthComponent::OnTakeAnyDamage);
    }
}

void UDGHealthComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
    Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void UDGHealthComponent::OnTakeAnyDamage(AActor* DamagedActor, float Damage, const UDamageType* DamageType, AController* InstigatedBy, AActor* DamageCauser)
{
    if (Damage < .0f) return;
    SetHealth(Health - Damage);

    if (IsDead())
    {
        Killed(InstigatedBy);
    }
}

void UDGHealthComponent::SetHealth(float NewHealth)
{
    Health = FMath::Clamp(NewHealth, 0.0f, MaxHealth);

    if (!Health)
    {
        OnBecomeDead.Broadcast();
    }

    UE_LOG(LogTemp, Display, TEXT("Health: %f"), Health);
}

void UDGHealthComponent::Killed(AController* KillerController)
{
    if (!GetWorld()) return;
    const auto GameMode = GetWorld()->GetAuthGameMode<ADGGameModeBase>();
    if (!GameMode) return;

    const auto ComponentPawnOwner = Cast<APawn>(GetOwner());
    const auto VictimController = ComponentPawnOwner ? ComponentPawnOwner->Controller : nullptr;
    GameMode->Killed(VictimController, KillerController);
}
