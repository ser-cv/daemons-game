// For Daemons and something else videogame purpose only

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "DGFirstPersonCharacter.generated.h"

class USkeletalMeshComponent;
class UCameraComponent;
class UInputComponent;
class UInputAction;
class UInputMappingContext;
struct FInputActionValue;
class UDGWeaponComponent;
class UDGHealthComponent;
class UDGCharacterMovement;

UCLASS()
class DAEMONS_API ADGFirstPersonCharacter : public ACharacter
{
    GENERATED_BODY()

public:
    ADGFirstPersonCharacter(const FObjectInitializer& ObjectInitializer);

protected:
    UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = Mesh)
    TObjectPtr<USkeletalMeshComponent> FirstPersonMesh;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
    TObjectPtr<UCameraComponent> FirstPersonCameraComponent;

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
    TObjectPtr<UInputAction> SprintAction;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
    TObjectPtr<UInputAction> CrouchAction;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
    TObjectPtr<UInputAction> CrawlAction;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
    TObjectPtr<UDGWeaponComponent> WeaponComponent;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
    TObjectPtr<UDGHealthComponent> HealthComponent;

protected:
    virtual void BeginPlay() override;

    void Move(const FInputActionValue& Value);
    void Look(const FInputActionValue& Value);
    void TrySprint(const FInputActionValue& Value);
    void TryCrouch(const FInputActionValue& Value);
    void TryCrawl();

public:
    virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
    virtual void PossessedBy(AController* NewController) override;
    virtual void PostInitializeComponents() override;

private:
    UPROPERTY()
    TObjectPtr<UDGCharacterMovement> CustomCharacterMovement;

    void TryFire(const FInputActionValue& Value);
};
