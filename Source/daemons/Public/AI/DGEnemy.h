// For Daemons and something else videogame purpose only

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Interfaces/DGCombatInterface.h"
#include "DGEnemy.generated.h"

class UBehaviorTree;
class UAnimMontage;

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
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Animation")
    TObjectPtr<UAnimMontage> ReactionAnimMontage;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Animation")
    TObjectPtr<UAnimMontage> LightMeeleAttackMontage;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Animation")
    TArray<UAnimMontage*> DeathAnimMontages;


	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
};
