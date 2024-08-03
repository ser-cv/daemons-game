// For Daemons and something else videogame purpose only

#include "Player/DGFirstPersonCharacter.h"
#include "Camera/CameraComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputActionValue.h"
#include "Components/DGWeaponComponent.h"

ADGFirstPersonCharacter::ADGFirstPersonCharacter()
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

void ADGFirstPersonCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
    Super::SetupPlayerInputComponent(PlayerInputComponent);

    if (const auto EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent))
    {
        EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ADGFirstPersonCharacter::Move);
        EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &ADGFirstPersonCharacter::Look);

        EnhancedInputComponent->BindAction(FireAction, ETriggerEvent::Triggered, this, &ADGFirstPersonCharacter::TryFire);
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

    WeaponComponent->SetCompToAttachWeapons(FirstPersonMesh);
    WeaponComponent->InitWeapons();
}

void ADGFirstPersonCharacter::TryFire(const FInputActionValue& Value)
{
    if (!WeaponComponent.Get()) return;

    Value.Get<bool>() ? WeaponComponent->StartFire() : WeaponComponent->StopFire();
}
