#pragma once

#include "DGCoreTypes.generated.h"

UENUM(BlueprintType)
enum class EItemType : uint8
{
    MAIN_WEAPON
};

USTRUCT(BlueprintType)
struct FItemData
{
    GENERATED_USTRUCT_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int32 Amount;
};