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
#include "Kismet/GameplayStatics.h"
#include "Player/DGPlayerController.h"

ADGCharacterBase::ADGCharacterBase(const FObjectInitializer& ObjectInitializer)
{
    PrimaryActorTick.bCanEverTick = true;

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

    SetActorTickEnabled(false);

    // Defaults
    CharacterMovementComp = GetCharacterMovement();
    DefaultWalkSpeed = CharacterMovementComp->MaxWalkSpeed;
}

void ADGCharacterBase::Tick(float DeltaTime)
{
    if (bIsDashing)
    {
        CharacterMovementComp->AddForce(CalculateDashForce());
    }
}

void ADGCharacterBase::Dash()
{
    if (bDashCooldown == false) return;

    UWorld* CurrentWorld = GetWorld();
    if (CurrentWorld == nullptr) return;

    bDashCooldown = true;
    SetActorTickEnabled(true);
    bIsDashing = true;

    // Set timer to stop dashing
    FTimerHandle TimerHandle;
    CurrentWorld->GetTimerManager().SetTimer(TimerHandle, this, &ADGCharacterBase::StopDashing, DashActiveTime, false);

    // Set timer for dash cooldown end
    FTimerHandle TimerHandleCD;
    CurrentWorld->GetTimerManager().SetTimer(TimerHandleCD, this, &ADGCharacterBase::EndDashCooldown, DashCooldownTime, false);
}

void ADGCharacterBase::StopDashing()
{
    bIsDashing = false;

    if (bIsCrouchedState) return;
    SetActorTickEnabled(false);
}

void ADGCharacterBase::EndDashCooldown()
{
    bDashCooldown = false;
}

FVector ADGCharacterBase::CalculateDashForce()
{
    FVector DashForce = MovementInput.X * GetActorRightVector() + MovementInput.Y * GetActorForwardVector();
    DashForce.Z = 0;

    if (DashForce.IsNearlyZero())
    {
        DashForce = GetActorForwardVector();
    }

    DashForce.Normalize(0.0001);

    if (CharacterMovementComp->IsMovingOnGround())
    {
        DashForce *= 100000 * DashSpeed;
    }
    else
    {
        DashForce *= 50000 * DashSpeed;
    }

    return DashForce;
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

    PlayerController = Cast<ADGPlayerController>(NewController);
    if (PlayerController)
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

        //EnhancedInputComponent->BindAction(PrimaryAttackAction, ETriggerEvent::Started, WeaponComponent.Get(), &UDGWeaponComponent::StartFire);
        //EnhancedInputComponent->BindAction(PrimaryAttackAction, ETriggerEvent::Completed, WeaponComponent.Get(), &UDGWeaponComponent::StopFire);

        //EnhancedInputComponent->BindAction(ReloadAction, ETriggerEvent::Completed, WeaponComponent.Get(), &UDGWeaponComponent::ReloadWeapon);

        EnhancedInputComponent->BindAction(AccelerateAction, ETriggerEvent::Started, this, &ADGCharacterBase::HandleAcceleration);

        EnhancedInputComponent->BindAction(CrouchAction, ETriggerEvent::Started, this, &ADGCharacterBase::HandleCrouch);

        EnhancedInputComponent->BindAction(InteractAction, ETriggerEvent::Started, this, &ADGCharacterBase::Interact);
        EnhancedInputComponent->BindAction(InteractAction, ETriggerEvent::Completed, this, &ADGCharacterBase::CancelInteraction);
    
        // Weapon switch
        EnhancedInputComponent->BindAction(LastWeaponAction, ETriggerEvent::Started, WeaponComponent.Get(), &UDGWeaponComponent::HandleLastWeaponInput);
        EnhancedInputComponent->BindAction(NextWeaponAction, ETriggerEvent::Started, WeaponComponent.Get(), &UDGWeaponComponent::HandleNextWeaponInput);
        EnhancedInputComponent->BindAction(PreviousWeaponAction, ETriggerEvent::Started, WeaponComponent.Get(), &UDGWeaponComponent::HandlePreviousWeaponInput);
        EnhancedInputComponent->BindAction(SlotOneAction, ETriggerEvent::Started, WeaponComponent.Get(), &UDGWeaponComponent::HandleSlotOneInput);
        EnhancedInputComponent->BindAction(SlotTwoAction, ETriggerEvent::Started, WeaponComponent.Get(), &UDGWeaponComponent::HandleSlotTwoInput);
        EnhancedInputComponent->BindAction(SlotThreeAction, ETriggerEvent::Started, WeaponComponent.Get(), &UDGWeaponComponent::HandleSlotThreeInput);
        EnhancedInputComponent->BindAction(SlotFourAction, ETriggerEvent::Started, WeaponComponent.Get(), &UDGWeaponComponent::HandleSlotFourInput);
        EnhancedInputComponent->BindAction(SlotFiveAction, ETriggerEvent::Started, WeaponComponent.Get(), &UDGWeaponComponent::HandleSlotFiveInput);
    
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
