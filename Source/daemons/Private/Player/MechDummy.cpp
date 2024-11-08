// For Daemons and something else videogame purpose only


#include "Player/MechDummy.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/CapsuleComponent.h"

AMechDummy::AMechDummy(const FObjectInitializer& ObjectInitializer) 
{
    CapsuleComponent = CreateDefaultSubobject<UCapsuleComponent>("Capsule");
    SetRootComponent(CapsuleComponent);

    MechSkeletalMesh = CreateDefaultSubobject<USkeletalMeshComponent>("MechMesh");
    MechSkeletalMesh->SetupAttachment(CapsuleComponent);
}

bool AMechDummy::CanTakeInHands() const
{
    return false;
}

FItemData& AMechDummy::GetItemData()
{
    return ItemData;
}

UStaticMeshComponent* AMechDummy::GetMesh()
{
    return nullptr;
}

void AMechDummy::Interact()
{
    Destroy();
}
