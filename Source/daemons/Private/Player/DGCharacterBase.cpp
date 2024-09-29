// For Daemons and something else videogame purpose only


#include "Player/DGCharacterBase.h"
#include "Camera/CameraComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputActionValue.h"
#include "Components/DGWeaponComponent.h"
#include "Components/DGHealthComponent.h"
#include "Interfaces/DGInteractionInterface.h"
#include "GameFramework/CharacterMovementComponent.h"

ADGCharacterBase::ADGCharacterBase(const FObjectInitializer& ObjectInitializer)
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

void ADGCharacterBase::BeginPlay()
{
    Super::BeginPlay();

    CharacterMovementComp = GetCharacterMovement();
    DefaultWalkSpeed = CharacterMovementComp->MaxWalkSpeed;
}

void ADGCharacterBase::PostInitializeComponents()
{
    Super::PostInitializeComponents();

    check(HealthComponent);
    check(WeaponComponent);

    WeaponComponent->SetCompToAttachWeapons(FirstPersonMesh);
    WeaponComponent->InitWeapons();
}

void ADGCharacterBase::PossessedBy(AController* NewController)
{
    Super::PossessedBy(NewController);

    if (const APlayerController* PlayerController = Cast<APlayerController>(NewController))
    {
        if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
        {
            Subsystem->AddMappingContext(DefaultMappingContext, 0);
        }
    }
}

void ADGCharacterBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
    Super::SetupPlayerInputComponent(PlayerInputComponent);

    if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent))
    {
        EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ADGCharacterBase::Move);
        EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Completed, this, &ADGCharacterBase::Move);

        EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &ADGCharacterBase::Look);

        EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Started, this, &ACharacter::Jump);
        EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &ACharacter::StopJumping);

        EnhancedInputComponent->BindAction(PrimaryAttackAction, ETriggerEvent::Started, WeaponComponent.Get(), &UDGWeaponComponent::StartFire);
        EnhancedInputComponent->BindAction(PrimaryAttackAction, ETriggerEvent::Completed, WeaponComponent.Get(), &UDGWeaponComponent::StopFire);

        EnhancedInputComponent->BindAction(SwitchWeaponAction, ETriggerEvent::Completed, WeaponComponent.Get(), &UDGWeaponComponent::SwitchWeapons);

        EnhancedInputComponent->BindAction(ReloadAction, ETriggerEvent::Completed, WeaponComponent.Get(), &UDGWeaponComponent::ReloadWeapon);

        EnhancedInputComponent->BindAction(AccelerateAction, ETriggerEvent::Started, this, &ADGCharacterBase::HandleAcceleration);

        EnhancedInputComponent->BindAction(CrouchAction, ETriggerEvent::Started, this, &ADGCharacterBase::HandleCrouch);

        EnhancedInputComponent->BindAction(InteractAction, ETriggerEvent::Triggered, this, &ADGCharacterBase::Interact);
    }
}

void ADGCharacterBase::Move(const FInputActionValue& Value)
{
    if (!Controller) return;
    const auto MovementVector = Value.Get<FVector2D>();
    MovementInput = Value.Get<FVector2D>();

    AddMovementInput(GetActorForwardVector(), MovementVector.Y);
    AddMovementInput(GetActorRightVector(), MovementVector.X);

    if (MovementInput.Y < 1)
    {
        StopSprinting();
    }
}

void ADGCharacterBase::Look(const FInputActionValue& Value)
{
    if (!Controller) return;
    const auto LookAxisVector = Value.Get<FVector2D>();

    AddControllerYawInput(LookAxisVector.X * Sensitivity);
    AddControllerPitchInput(LookAxisVector.Y * Sensitivity);
}


