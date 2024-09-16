// For Daemons and something else videogame purpose only

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "DGPlayerCharacter.generated.h"

class USkeletalMeshComponent;
class UCameraComponent;
class UInputComponent;
class UInputAction;
class UInputMappingContext;
struct FInputActionValue;
class UDGWeaponComponent;
class UDGHealthComponent;

UCLASS()
class DAEMONS_API ADGPlayerCharacter : public ACharacter
{
    GENERATED_BODY()

public:
    ADGPlayerCharacter(const FObjectInitializer& ObjectInitializer);

protected:
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
    TObjectPtr<UInputAction> FireAction;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
    TObjectPtr<UInputAction> SwitchWeaponsAction;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
    TObjectPtr<UInputAction> ReloadAction;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
    TObjectPtr<UInputAction> AccelerateAction;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
    TObjectPtr<UInputAction> CrouchAction;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
    TObjectPtr<UInputAction> InteractAction;

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

    // Parameters

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Interaction", meta = (ClampMin = "0", ClampMax = "1000"))
    float InteractionDistance{300.f};

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Config")
    FName ItemSocketName{"ItemSocket"};

    float DefaultWalkSpeed;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Parameters")
    float SprintSpeed{800.f};

    // States
    UPROPERTY()
    bool bIsCrouching{false};
    UPROPERTY()
    bool bIsSprinting{false};

    virtual void BeginPlay() override;

    // Input methods
    void Move(const FInputActionValue& Value);
    void Look(const FInputActionValue& Value);
    void HandleAcceleration();
    void HandleCrouch();
    void Interact();

public:
    virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
    virtual void PossessedBy(AController* NewController) override;
    virtual void PostInitializeComponents() override;

private:
    UPROPERTY()
    TObjectPtr<AActor> AttachedActor;
};
