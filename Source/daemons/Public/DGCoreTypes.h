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

UENUM(BlueprintType)
enum class EPhase : uint8
{
    No_Phase,
    Phase_1,
    Phase_2,
    Phase_3,
    Phase_4,
    Phase_5,
    Phase_6,
    Phase_7,
    Phase_8,
    Phase_9
};

USTRUCT(BlueprintType)
struct FItemData
{
    GENERATED_USTRUCT_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int32 Amount;
};