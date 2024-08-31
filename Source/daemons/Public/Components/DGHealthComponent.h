// For Daemons and something else videogame purpose only

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "DGHealthComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_SPARSE_DELEGATE(FOnBecpmeDeadSignature, UDGHealthComponent, OnBecomeDead);

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class DAEMONS_API UDGHealthComponent : public UActorComponent
{
    GENERATED_BODY()

public:
    UDGHealthComponent();

    UPROPERTY(BlueprintAssignable, Category = "Components|Activation")
    FOnBecpmeDeadSignature OnBecomeDead;

protected:
    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Health", meta = (ClampMin = "0.0", ClampMax = "1000.0"))
    float MaxHealth = 100.0f;

    virtual void BeginPlay() override;

public:
    virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:
    float Health = 0.0f;

    UFUNCTION()
    void OnTakeAnyDamage(AActor* DamagedActor, float Damage, const class UDamageType* DamageType, class AController* InstigatedBy, AActor* DamageCauser);

    void SetHealth(float NewHealth);
};
