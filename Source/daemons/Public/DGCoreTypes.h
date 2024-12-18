#pragma once

#include "DGCoreTypes.generated.h"

UENUM(BlueprintType)
enum class EItemType : uint8
{
    MAIN_WEAPON,
    EXTRA_WEAPON
};

UENUM(BlueprintType)
enum class EAIBehaviorState : uint8
{
    No_Aim,
    Damage_Received,
    Sight_Detected,
    Hearing_Detected,
    Team_Reported,
    Lost_Aim
};

USTRUCT(BlueprintType)
struct FItemData
{
    GENERATED_USTRUCT_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int32 Amount;
};