// For Daemons and something else videogame purpose only

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "DGCharacterBase.generated.h"

class USkeletalMeshComponent;
class UCameraComponent;
class UInputComponent;
class UInputAction;
class UInputMappingContext;
struct FInputActionValue;
class UDGWeaponComponent;
class UDGHealthComponent;
class ADGPlayerController;

UCLASS()
class DAEMONS_API ADGCharacterBase : public ACharacter
{
    GENERATED_BODY()

public:
    ADGCharacterBase(const FObjectInitializer& ObjectInitializer);

protected:
    virtual void BeginPlay() override;
    virtual void Tick(float DeltaTime);

    // Input

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
    TObjectPtr<UInputMappingContext> DefaultMappingContext;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
    TObjectPtr<UInputAction> MoveAction;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
    TObjectPtr<UInputAction> LookAction;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
    TObjectPtr<UInputAction> JumpAction;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
    TObjectPtr<UInputAction> PrimaryAttackAction;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
    TObjectPtr<UInputAction> AlternativeGunModeAction;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
    TObjectPtr<UInputAction> ReloadAction;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
    TObjectPtr<UInputAction> AccelerateAction;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
    TObjectPtr<UInputAction> CrouchAction;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
    TObjectPtr<UInputAction> InteractAction;

    // Weapon switch actions
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
    TObjectPtr<UInputAction> SwitchWeaponAction;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
    TObjectPtr<UInputAction> NextWeaponAction;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
    TObjectPtr<UInputAction> PreviousWeaponAction;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
    TObjectPtr<UInputAction> SlotOneAction;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
    TObjectPtr<UInputAction> SlotTwoAction;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
    TObjectPtr<UInputAction> SlotThreeAction;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
    TObjectPtr<UInputAction> SlotFourAction;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
    TObjectPtr<UInputAction> SlotFiveAction;

    // Components

    UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = Mesh)
    TObjectPtr<USkeletalMeshComponent> FirstPersonMesh;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
    TObjectPtr<UCameraComponent> FirstPersonCameraComponent;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
    TObjectPtr<UDGWeaponComponent> WeaponComponent;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
    TObjectPtr<UDGHealthComponent> HealthComponent;

    UCharacterMovementComponent* CharacterMovementComp;

    ADGPlayerController* PlayerController;

    // Parameters

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Interaction", meta = (ClampMin = "0", ClampMax = "1000"))
    float InteractionDistance{300.f};

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Config")
    FName ItemSocketName{"ItemSocket"};

    float DefaultWalkSpeed{};

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Parameters")
    float SprintSpeed{800.f};

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Parameters")
    float DashSpeed{25.f};

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Parameters")
    float Sensitivity{0.5f};

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Parameters");
    float DashCooldownTime{0.5f};

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Parameters");
    float DashActiveTime{0.2f};

    // States

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "States")
    bool bIsSprinting{false};

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "States")
    bool bIsDashing{false};

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "States")
    bool bIsCrouchedState{false};

    bool bDashCooldown{false};

    // Input methods

    virtual void Move(const FInputActionValue& Value);
    virtual void Look(const FInputActionValue& Value);
    virtual void HandleCrouch() PURE_VIRTUAL(ADGCharacterBase::HandleCrouch, );
    virtual void Interact() PURE_VIRTUAL(ADGCharacterBase::Interact, );
    virtual void CancelInteraction() PURE_VIRTUAL(ADGCharacterBase::CancelInteraction, );

    // Sprint and dash
    virtual void HandleAcceleration() PURE_VIRTUAL(ADGCharacterBase::HandleAcceleration, );
    virtual void Sprint() PURE_VIRTUAL(ADGCharacterBase::Sprint, );
    virtual void StopSprinting() PURE_VIRTUAL(ADGCharacterBase::StopSprinting, );
    void Dash();
    void StopDashing();
    void EndDashCooldown();

    // Calculations
    UPROPERTY()
    FVector2D MovementInput;

    FVector CalculateDashForce();

public:
    virtual void PostInitializeComponents() override;
    void PossessedBy(AController* NewController);
    virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:
    UPROPERTY()
    TObjectPtr<AActor> AttachedActor;
};
