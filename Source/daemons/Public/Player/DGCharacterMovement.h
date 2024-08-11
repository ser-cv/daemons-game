// For Daemons and something else videogame purpose only

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "DGCharacterMovement.generated.h"

// clang-format off
UENUM(BlueprintType)
enum ECustomMovementMode : uint8
{
	CMOVE_None			UMETA(DisplayName = "None"),
	CMOVE_Sprint		UMETA(DisplayName = "Sprint"),
	CMOVE_MAX			UMETA(Hidden)
};
// clang-format on

UCLASS()
class DAEMONS_API UDGCharacterMovement : public UCharacterMovementComponent
{
	GENERATED_BODY()

public:
	bool bWantsToSprint{false};

	virtual void UpdateCharacterStateBeforeMovement(float DeltaSeconds) override;
	virtual float GetMaxSpeed() const override;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float SprintSpeed{600.f};
	
protected:
	virtual void InitializeComponent() override;
	virtual void PhysCustom(float DeltaTime, int32 Iterations) override;
	
private:
    void PhysSprint(float DeltaTime, int32 Iterations);

	bool IsCustomMovementMode(const ECustomMovementMode InCustomMovementMode) const;

};
