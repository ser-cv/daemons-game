// For Daemons and something else videogame purpose only

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interfaces/DGInteractionInterface.h"
#include "MechDummy.generated.h"

class UCapsuleComponent;

UCLASS()
class DAEMONS_API AMechDummy : public AActor, public IDGInteractionInterface
{
    GENERATED_BODY()

public:
    AMechDummy(const FObjectInitializer& ObjectInitializer);

    virtual bool CanTakeInHands() const override;
    virtual FItemData& GetItemData() override;
    FItemData ItemData;
    virtual UStaticMeshComponent* GetMesh() override;

    virtual void Interact() override;

protected:
    UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "Components")
    TObjectPtr<USkeletalMeshComponent> MechSkeletalMesh;

    UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "Components")
	TObjectPtr<UCapsuleComponent> CapsuleComponent;
};
