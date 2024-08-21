// For Daemons and something else videogame purpose only

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interfaces/DGInteractionInterface.h"
#include "DGCoreTypes.h"
#include "DGUsableStaticMeshActor.generated.h"

class USphereComponent;

UCLASS()
class DAEMONS_API ADGUsableStaticMeshActor : public AActor, public IDGInteractionInterface
{
	GENERATED_BODY()
	
public:	
	ADGUsableStaticMeshActor();

	/* Interface */
	virtual bool CanTakeInHands() const override;
	virtual FItemData& GetItemData() override;
	virtual void Interact() override;

	virtual UStaticMeshComponent* GetMesh() override { return Mesh; }

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Components")
    TObjectPtr<UStaticMeshComponent> Mesh;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Components")
    TObjectPtr<USphereComponent> CollisionComp;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Config")
	bool bCanTake{true};

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Config")
	FItemData ItemData;

	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

};
