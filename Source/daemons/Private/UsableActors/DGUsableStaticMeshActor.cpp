// For Daemons and something else videogame purpose only


#include "UsableActors/DGUsableStaticMeshActor.h"
#include "Components/SphereComponent.h"

ADGUsableStaticMeshActor::ADGUsableStaticMeshActor()
{
	PrimaryActorTick.bCanEverTick = true;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
    Mesh->SetMobility(EComponentMobility::Movable);
    Mesh->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECR_Ignore);

    CollisionComp = CreateDefaultSubobject<USphereComponent>("CollisionComponent");
    CollisionComp->SetupAttachment(Mesh);
    CollisionComp->SetSphereRadius(50.f);
}

bool ADGUsableStaticMeshActor::CanTakeInHands() const
{
    return bCanTake;
}

FItemData& ADGUsableStaticMeshActor::GetItemData()
{
    return ItemData;
}

void ADGUsableStaticMeshActor::Interact() 
{

}

void ADGUsableStaticMeshActor::BeginPlay()
{
	Super::BeginPlay();
	
}

void ADGUsableStaticMeshActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

