// For Daemons and something else videogame purpose only

#include "AI/DGAICharacter.h"
#include "AI/DGAIController.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/DGHealthComponent.h"
#include "Components/CapsuleComponent.h"
#include "BrainComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/BehaviorTreeTypes.h"

ADGAICharacter::ADGAICharacter()
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

void ADGAICharacter::DoLightMeeleAttack()
{
    if (!CanAttack()) return;
    PlayAnimMontage(LightMeeleAttackMontage);
}

void ADGAICharacter::DoHeavyMeeleAttack() {}

void ADGAICharacter::DoRangeAttack(AActor* AimActor)
{
    FocusedAimActor = AimActor;
    if (!CanAttack()) return;
    PlayAnimMontage(RangeAttackMontage);
}

void ADGAICharacter::BeginPlay()
{
    Super::BeginPlay();
}

void ADGAICharacter::PostInitializeComponents()
{
    Super::PostInitializeComponents();

    if (HealthComponent && !HealthComponent->OnBecomeDead.IsBound())
    {
        HealthComponent->OnBecomeDead.AddUniqueDynamic(this, &ADGAICharacter::OnBecomeDead);
    }

    InitAnimationNotifies();
}

float ADGAICharacter::TakeDamage(float Damage, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
    const bool bIsChance = (FMath::SRand() * 100.f) < DamageReactionChance;
    const bool bCanReaction = bIsChance && (!GetCurrentMontage() || (GetCurrentMontage() != ReactionAnimMontage.Get()));
    if (bCanReaction)
    {
        PlayAnimMontage(ReactionAnimMontage);
    }

    return Super::TakeDamage(Damage, DamageEvent, EventInstigator, DamageCauser);
}

void ADGAICharacter::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
    GEngine->AddOnScreenDebugMessage(-1, 0, FColor::Green, FString::Printf(TEXT("%s"), GetCurrentMontage() ? TEXT("false") : TEXT("true")));
}

void ADGAICharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
    Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void ADGAICharacter::OnBecomeDead()
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

bool ADGAICharacter::CanAttack() const
{
    return GetCurrentMontage() ? false : true;
}

void ADGAICharacter::InitAnimationNotifies() 
{
    if (GetMesh() && GetMesh()->GetAnimInstance())
    {
        GetMesh()->GetAnimInstance()->OnPlayMontageNotifyBegin.AddDynamic(this, &ADGAICharacter::OnPlayMontageAnimNotify);
    }
}

void ADGAICharacter::HandleRangeAttack() 
{
    //GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Green, "HandleRangeAttack");
    if (!GetWorld() || !GetMesh() || !FocusedAimActor) return;

    const FVector SocketLocation = GetMesh()->GetSocketLocation(RightHandSocketName);
    const FVector FocusedAimLocation = FocusedAimActor->GetActorLocation();
    const auto Direction = (FocusedAimLocation - SocketLocation).GetSafeNormal();

    DrawDebugLine(GetWorld(), SocketLocation, FocusedAimLocation, FColor::Orange, false, 2.f, 0u, 2.f);
}

void ADGAICharacter::OnPlayMontageAnimNotify(FName NotifyName, const FBranchingPointNotifyPayload& BranchingPointPayload) 
{
    //GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Green, "OnPlayMontageAnimNotify");
    if (NotifyName == RangeAttackNotifyName)
    {
        HandleRangeAttack();
    }
}
