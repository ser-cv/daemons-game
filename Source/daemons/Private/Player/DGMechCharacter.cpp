// For Daemons and something else videogame purpose only


#include "Player/DGMechCharacter.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputActionValue.h"

ADGMechCharacter::ADGMechCharacter()
{
	PrimaryActorTick.bCanEverTick = false;

}

void ADGMechCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

void ADGMechCharacter::Move(const FInputActionValue& Value) 
{

}

void ADGMechCharacter::Look(const FInputActionValue& Value) 
{

}

void ADGMechCharacter::HandleAcceleration() 
{

}

void ADGMechCharacter::Dash() 
{

}

void ADGMechCharacter::Interact() 
{

}

void ADGMechCharacter::CancelInteraction() 
{

}

void ADGMechCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent))
    {
        EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ADGMechCharacter::Move);

        EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &ADGMechCharacter::Look);

        EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Started, this, &ACharacter::Jump);
        EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &ACharacter::StopJumping);

        EnhancedInputComponent->BindAction(AccelerateAction, ETriggerEvent::Started, this, &ADGMechCharacter::HandleAcceleration);

        EnhancedInputComponent->BindAction(InteractAction, ETriggerEvent::Started, this, &ADGMechCharacter::Interact);
        EnhancedInputComponent->BindAction(InteractAction, ETriggerEvent::Completed, this, &ADGMechCharacter::CancelInteraction);
    }
}

