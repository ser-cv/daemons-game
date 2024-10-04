// For Daemons and something else videogame purpose only


#include "AI/DGEnemy.h"
#include "AI/DGAIController.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/DGHealthComponent.h"
#include "Components/CapsuleComponent.h"
#include "BrainComponent.h"

ADGEnemy::ADGEnemy()
{
	AutoPossessAI = EAutoPossessAI::Disabled;
	AIControllerClass = ADGAIController::StaticClass();

	bUseControllerRotationYaw = false;
    if (GetCharacterMovement())
    {
        GetCharacterMovement()->bUseControllerDesiredRotation = true;
        GetCharacterMovement()->RotationRate = FRotator(0.0f, 200.0f, 0.0f);
    }

	PrimaryActorTick.bCanEverTick = true;

	HealthComponent = CreateDefaultSubobject<UDGHealthComponent>("HealthComponent");
}

void ADGEnemy::DoLightMeeleAttack() 
{
	PlayAnimMontage(LightMeeleAttackMontage);
}

void ADGEnemy::DoHeavyMeeleAttack() {}

bool ADGEnemy::CanAttack() const
{
	return GetCurrentMontage() ? false : true;
}

void ADGEnemy::BeginPlay()
{
	Super::BeginPlay();
}

void ADGEnemy::PostInitializeComponents() 
{
	Super::PostInitializeComponents();

	if (HealthComponent && !HealthComponent->OnBecomeDead.IsBound())
    {
		HealthComponent->OnBecomeDead.AddUniqueDynamic(this, &ADGEnemy::OnBecomeDead);
	}
}

float ADGEnemy::TakeDamage(float Damage, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
    const bool bHasChance = (FMath::SRand() * 100.f) < DamageReactionChance;
    const bool bCanReaction = bHasChance && (!GetCurrentMontage() || (GetCurrentMontage() != ReactionAnimMontage.Get()));
    if (bCanReaction) 
    {
        PlayAnimMontage(ReactionAnimMontage);
    }

    return Super::TakeDamage(Damage, DamageEvent, EventInstigator, DamageCauser);
}

void ADGEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
    GEngine->AddOnScreenDebugMessage(-1, 0, FColor::Green, FString::Printf(TEXT("%s"), GetCurrentMontage() ? TEXT("false") : TEXT("true")));
}

void ADGEnemy::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void ADGEnemy::OnBecomeDead() 
{
	GetCharacterMovement()->DisableMovement();

    SetLifeSpan(5.f);
        
    GetCapsuleComponent()->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);

    GetMesh()->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
    GetMesh()->SetSimulatePhysics(true);

	const auto AIController = Cast<AAIController>(Controller);
    if (AIController && AIController->BrainComponent)
    {
        AIController->BrainComponent->Cleanup();
    }
}

