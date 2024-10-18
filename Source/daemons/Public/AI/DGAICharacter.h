// For Daemons and something else videogame purpose only

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Interfaces/DGCombatInterface.h"
#include "DGAICharacter.generated.h"

class UBehaviorTree;
class UAnimMontage;
class UDGHealthComponent;

UCLASS()
class DAEMONS_API ADGAICharacter : public ACharacter, public IDGCombatInterface
{
    GENERATED_BODY()

public:
    ADGAICharacter();

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "AI")
    TObjectPtr<UBehaviorTree> BehaviorTreeAsset;

    // CombatInterface
    virtual void DoLightMeeleAttack() override;
    virtual void DoHeavyMeeleAttack() override;

    virtual void DoRangeAttack(AActor* AimActor) override;

protected:
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
    TObjectPtr<UDGHealthComponent> HealthComponent;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Animation")
    TObjectPtr<UAnimMontage> ReactionAnimMontage;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Animation")
    TObjectPtr<UAnimMontage> LightMeeleAttackMontage;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Animation")
    TObjectPtr<UAnimMontage> RangeAttackMontage;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Animation")
    TArray<UAnimMontage*> DeathAnimMontages;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animation", meta = (Clampmin = "0", clampmax = "100"))
    float DamageReactionChance{50.f};

    // for ranger
    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Attack")
    TSubclassOf<AActor> ProjectileClass;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Attack")
    FName RightHandSocketName{"RightHandSocket"};

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Attack")
    FName RangeAttackNotifyName{"RangeAttackNotify"};

    virtual void BeginPlay() override;
    virtual void PostInitializeComponents() override;
    virtual float TakeDamage(float Damage, struct FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;

public:
    virtual void Tick(float DeltaTime) override;

    virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

    UFUNCTION()
    void OnBecomeDead();

private:
    UPROPERTY()
    TObjectPtr<AActor> FocusedAimActor;

    bool CanAttack() const;

    void InitAnimationNotifies();
    void HandleRangeAttack();

    UFUNCTION()
    void OnPlayMontageAnimNotify(FName NotifyName, const FBranchingPointNotifyPayload& BranchingPointPayload);
};
