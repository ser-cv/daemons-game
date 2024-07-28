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

UCLASS()
class DAEMONS_API ADGFirstPersonCharacter : public ACharacter
{
    GENERATED_BODY()

public:
    ADGFirstPersonCharacter();

protected:
    UPROPERTY(VisibleDefaultsOnly, Category = Mesh)
    TObjectPtr<USkeletalMeshComponent> Mesh1P;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
    TObjectPtr<UCameraComponent> FirstPersonCameraComponent;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
    TObjectPtr<UInputMappingContext> DefaultMappingContext;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
    TObjectPtr<UInputAction> MoveAction;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
    TObjectPtr<UInputAction> LookAction;

protected:
    virtual void BeginPlay() override;

    void Move(const FInputActionValue& Value);

    void Look(const FInputActionValue& Value);

public:
    virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
    virtual void PossessedBy(AController* NewController) override;
};
