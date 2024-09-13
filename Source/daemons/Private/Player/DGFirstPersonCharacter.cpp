// For Daemons and something else videogame purpose only

#include "Player/DGFirstPersonCharacter.h"
#include "Player/DGCharacterMovement.h"
#include "Camera/CameraComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputActionValue.h"
#include "Components/DGWeaponComponent.h"
#include "Components/DGHealthComponent.h"
#include "Interfaces/DGInteractionInterface.h"

ADGFirstPersonCharacter::ADGFirstPersonCharacter(const FObjectInitializer& ObjectInitializer)
    : Super(ObjectInitializer.SetDefaultSubobjectClass<UDGCharacterMovement>(ACharacter::CharacterMovementComponentName))
{
    PrimaryActorTick.bCanEverTick = false;

    FirstPersonCameraComponent = CreateDefaultSubobject<UCameraComponent>("FirstPersonCamera");
    FirstPersonCameraComponent->SetupAttachment(GetRootComponent());
    FirstPersonCameraComponent->bUsePawnControlRotation = true;

    FirstPersonMesh = CreateDefaultSubobject<USkeletalMeshComponent>("CharacterMesh");
    FirstPersonMesh->SetOnlyOwnerSee(true);
    FirstPersonMesh->SetupAttachment(FirstPersonCameraComponent);
    FirstPersonMesh->bCastDynamicShadow = false;
    FirstPersonMesh->CastShadow = false;

    WeaponComponent = CreateDefaultSubobject<UDGWeaponComponent>("WeaponComponent");
    HealthComponent = CreateDefaultSubobject<UDGHealthComponent>("HealthComponent");
}

void ADGFirstPersonCharacter::BeginPlay()
{
    Super::BeginPlay();
}

void ADGFirstPersonCharacter::Move(const FInputActionValue& Value)
{
    if (!Controller) return;
    const auto MovementVector = Value.Get<FVector2D>();

    AddMovementInput(GetActorForwardVector(), MovementVector.Y);
    AddMovementInput(GetActorRightVector(), MovementVector.X);
}

void ADGFirstPersonCharacter::Look(const FInputActionValue& Value)
{
    if (!Controller) return;
    const auto LookAxisVector = Value.Get<FVector2D>();

    AddControllerYawInput(LookAxisVector.X);
    AddControllerPitchInput(LookAxisVector.Y);
}

void ADGFirstPersonCharacter::TrySprint(const FInputActionValue& Value)
{
    const bool bWantsToSprint = Value.Get<bool>();
    CustomCharacterMovement->bWantsToSprint = bWantsToSprint;
}

void ADGFirstPersonCharacter::TryCrouch(const FInputActionValue& Value)
{
    if (!GetCharacterMovement()) return;
    const bool bCrouch = Value.Get<bool>();

    bCrouch ? Crouch() : UnCrouch();
}

void ADGFirstPersonCharacter::MakeInteraction()
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
            HitResult.GetActor()->AttachToComponent(FirstPersonMesh, AttachmentRules, ItemSocketName); //+socket name
            //inventory component -> AddToInventory(ActorToInteract->GetItemData()) 
            //Chech emty Item data and attach to hand
        }
        else
        {
            ActorToInteract->Interact();
        }
    }
}

void ADGFirstPersonCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
    Super::SetupPlayerInputComponent(PlayerInputComponent);

    if (const auto EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent))
    {
        EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ADGFirstPersonCharacter::Move);
        EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &ADGFirstPersonCharacter::Look);

        EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Started, this, &ACharacter::Jump);
        EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &ACharacter::StopJumping);

        EnhancedInputComponent->BindAction(FireAction, ETriggerEvent::Started, WeaponComponent.Get(), &UDGWeaponComponent::StartFire);
        EnhancedInputComponent->BindAction(FireAction, ETriggerEvent::Completed, WeaponComponent.Get(), &UDGWeaponComponent::StopFire);

        EnhancedInputComponent->BindAction(SwitchWeaponsAction, ETriggerEvent::Completed, WeaponComponent.Get(), &UDGWeaponComponent::SwitchWeapons);

        EnhancedInputComponent->BindAction(ReloadAction, ETriggerEvent::Completed, WeaponComponent.Get(), &UDGWeaponComponent::ReloadWeapon);

        EnhancedInputComponent->BindAction(SprintAction, ETriggerEvent::Triggered, this, &ADGFirstPersonCharacter::TrySprint);

        EnhancedInputComponent->BindAction(CrouchAction, ETriggerEvent::Triggered, this, &ADGFirstPersonCharacter::TryCrouch);

        EnhancedInputComponent->BindAction(MakeInteractionAction, ETriggerEvent::Triggered, this, &ADGFirstPersonCharacter::MakeInteraction);
    }
}

void ADGFirstPersonCharacter::PossessedBy(AController* NewController)
{
    Super::PossessedBy(NewController);

    if (const auto PlayerController = Cast<APlayerController>(NewController))
    {
        if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
        {
            Subsystem->AddMappingContext(DefaultMappingContext, 0);
        }
    }
}

void ADGFirstPersonCharacter::PostInitializeComponents()
{
    Super::PostInitializeComponents();

    check(HealthComponent);
    check(WeaponComponent);

    WeaponComponent->SetCompToAttachWeapons(FirstPersonMesh);
    WeaponComponent->InitWeapons();

    CustomCharacterMovement = GetCharacterMovement<UDGCharacterMovement>();

    check(CustomCharacterMovement);
}