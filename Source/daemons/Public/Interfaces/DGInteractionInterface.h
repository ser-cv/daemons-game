// For Daemons and something else videogame purpose only

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "DGCoreTypes.h"
#include "DGInteractionInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UDGInteractionInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class DAEMONS_API IDGInteractionInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	virtual bool CanTakeInHands() const = 0;
	virtual FItemData& GetItemData() = 0;
	virtual void Interact() = 0;

	virtual UStaticMeshComponent* GetMesh() = 0;
};
