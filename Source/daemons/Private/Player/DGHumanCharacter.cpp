// For Daemons and something else videogame purpose only

#include "Player/DGHumanCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Interfaces/DGInteractionInterface.h"
#include "Components/CapsuleComponent.h"
#include "Kismet/KismetStringLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "MechDummy.h"
#include "Player/DGPlayerController.h"

void ADGHumanCharacter::PossessedBy(AController* NewController)
{
    Super::PossessedBy(NewController);
}

void ADGHumanCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
    Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void ADGHumanCharacter::BeginPlay() 
{
    Super::BeginPlay();

    DefaultHalfHeight = GetCapsuleComponent()->GetScaledCapsuleHalfHeight();
    CrouchedHalfHeight = CharacterMovementComp->GetCrouchedHalfHeight();
}

void ADGHumanCharacter::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);


    // Crouching
    if (bIsCrouching)
    {
        NewHalfHeight -= CrouchAnimationSpeed * DeltaTime;
        NewHalfHeight = FMath::Clamp(NewHalfHeight, CrouchedHalfHeight, DefaultHalfHeight);
        GetCapsuleComponent()->SetCapsuleHalfHeight(NewHalfHeight);
        GEngine->AddOnScreenDebugMessage(-1, 0, FColor::Green, FString::SanitizeFloat(NewHalfHeight));
        
        if (NewHalfHeight == CrouchedHalfHeight)
        {
            bIsCrouching = false;
            Crouch();
            SetActorTickEnabled(false);
        }
    }
    else if (bIsUncrouching)
    {
        NewHalfHeight += CrouchAnimationSpeed * DeltaTime;
        NewHalfHeight = FMath::Clamp(NewHalfHeight, CrouchedHalfHeight, DefaultHalfHeight);
        GetCapsuleComponent()->SetCapsuleHalfHeight(NewHalfHeight);
        GEngine->AddOnScreenDebugMessage(-1, 0, FColor::Green, FString::SanitizeFloat(NewHalfHeight));

        if (NewHalfHeight == DefaultHalfHeight)
        {
            bIsUncrouching = false;
            bIsCrouchedState = false;
            UnCrouch();
            SetActorTickEnabled(false);
        }
    }
    GEngine->AddOnScreenDebugMessage(-1, 0, FColor::Green, UKismetStringLibrary::Conv_BoolToString(bIsCrouchedState));
}

void ADGHumanCharacter::HandleCrouch()
{
    if (CharacterMovementComp == nullptr) return;
    NewHalfHeight = GetCapsuleComponent()->GetScaledCapsuleHalfHeight();
    if (bIsCrouchedState)
    {
        SetActorTickEnabled(true);

        bIsUncrouching = true;
    }
    else if (CharacterMovementComp->IsMovingOnGround())
    {
        SetActorTickEnabled(true);

        bIsCrouching = true;
        bIsCrouchedState = true;
        StopSprinting();
    }
}

void ADGHumanCharacter::HandleAcceleration()
{
    if (bIsCrouchedState)
    {
        HandleCrouch();
    }

    if (MovementInput.IsNearlyZero()) return;

    if (MovementInput.Y > 0)
    {
        Sprint();

        if (CharacterMovementComp->IsMovingOnGround() == false || MovementInput.X != 0)
        {
            Dash();
        }
    }
    else
    {
        Dash();
    }
}

void ADGHumanCharacter::Sprint()
{
    if (CharacterMovementComp->IsMovingOnGround())
    {
        CharacterMovementComp->MaxWalkSpeed = SprintSpeed;
        bIsSprinting = true;
    }
}

void ADGHumanCharacter::StopSprinting()
{
    if (bIsSprinting)
    {
        CharacterMovementComp->MaxWalkSpeed = DefaultWalkSpeed;
        bIsSprinting = false;
    }
}

void ADGHumanCharacter::Interact()
{
    FVector ViewLocation;
    FRotator ViewRotation;
    Controller->GetPlayerViewPoint(ViewLocation, ViewRotation);

    const FVector TraceStart = ViewLocation;
    const FVector ViewDirection = ViewRotation.Vector();
    const FVector TraceEnd = TraceStart + ViewDirection * InteractionDistance;
    FCollisionQueryParams CollisionParams;
    CollisionParams.AddIgnoredActor(GetOwner());
    FHitResult HitResult;
    GetWorld()->LineTraceSingleByChannel(HitResult, TraceStart, TraceEnd, ECollisionChannel::ECC_Visibility, CollisionParams);

    DrawDebugLine(GetWorld(), TraceStart, TraceEnd, FColor::Emerald, false, 2.f, 0u, 2.f);

    if (HitResult.GetActor())
    {
        UE_LOG(LogTemp, Display, TEXT("%s"), *HitResult.GetActor()->GetName());
    }

    // Enter Mech if interacting with it
    if (AMechDummy* MechDummy = Cast<AMechDummy>(HitResult.GetActor()))
    {
        MechDummy->Interact();

        // TODO: create mech entering animation and then call function at the end of anim
        ADGPlayerController* PlayerController = Cast<ADGPlayerController>(
            UGameplayStatics::GetPlayerController(this, 0));
        PlayerController->CreateAndPossessMech(MechDummy->GetActorTransform());
        MechDummy->Interact();
        return;
    }

    if (const auto ActorToInteract = Cast<IDGInteractionInterface>(HitResult.GetActor()))
    {
        if (ActorToInteract->CanTakeInHands())
        {
            if (ActorToInteract->GetMesh() && HitResult.GetActor()->IsAttachedTo(this))
            {
                UE_LOG(LogTemp, Display, TEXT("detach"));
                ActorToInteract->GetMesh()->SetSimulatePhysics(true);
                return;
            }
            if (ActorToInteract->GetMesh())
            {
                ActorToInteract->GetMesh()->SetSimulatePhysics(false);
            }

            FAttachmentTransformRules AttachmentRules(EAttachmentRule::SnapToTarget, false);
            HitResult.GetActor()->AttachToComponent(FirstPersonMesh, AttachmentRules, ItemSocketName);  //+socket name
            // inventory component -> AddToInventory(ActorToInteract->GetItemData())
            // Chech emty Item data and attach to hand
        }
        else
        {
            ActorToInteract->Interact();
        }
    }
}

void ADGHumanCharacter::CancelInteraction() {}
