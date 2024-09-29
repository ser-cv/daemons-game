// For Daemons and something else videogame purpose only

#include "Player/DGHumanCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Interfaces/DGInteractionInterface.h"

void ADGHumanCharacter::PossessedBy(AController* NewController) 
{
    Super::PossessedBy(NewController);
}

void ADGHumanCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
    Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void ADGHumanCharacter::HandleCrouch()
{
    if (CharacterMovementComp == nullptr) return;
    if (bIsCrouching)
    {
        UnCrouch();
        bIsCrouching = false;
    }
    else if (CharacterMovementComp->IsMovingOnGround())
    {
        Crouch();
        bIsCrouching = true;
        StopSprinting();
    }
}

void ADGHumanCharacter::HandleAcceleration()
{
    if (bIsCrouching) return;
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
