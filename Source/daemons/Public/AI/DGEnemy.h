// For Daemons and something else videogame purpose only

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Interfaces/DGCombatInterface.h"
#include "DGEnemy.generated.h"

class UBehaviorTree;
class UAnimMontage;
class UDGHealthComponent;

UCLASS()
class DAEMONS_API ADGEnemy : public ACharacter, public IDGCombatInterface
{
	GENERATED_BODY()

public:
	ADGEnemy();

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "AI")
    TObjectPtr<UBehaviorTree> BehaviorTreeAsset;

	// CombatInterface
	virtual void DoLightMeeleAttack() override;
	virtual void DoHeavyMeeleAttack() override;
	virtual bool CanAttack() const override;

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
    TObjectPtr<UDGHealthComponent> HealthComponent;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Animation")
    TObjectPtr<UAnimMontage> ReactionAnimMontage;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Animation")
    TObjectPtr<UAnimMontage> LightMeeleAttackMontage;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Animation")
    TArray<UAnimMontage*> DeathAnimMontages;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config", meta = (Clampmin = "0", clampmax = "100"))
	float DamageReactionChance{50.f};

	virtual void BeginPlay() override;
	virtual void PostInitializeComponents() override;
	virtual float TakeDamage(float Damage, struct FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;

public:	
	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION()
	void OnBecomeDead();
};