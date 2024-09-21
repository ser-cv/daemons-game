// For Daemons and something else videogame purpose only


#include "AI/DGEnemy.h"
#include "AI/DGAIController.h"
#include "GameFramework/CharacterMovementComponent.h"

ADGEnemy::ADGEnemy()
{
	AutoPossessAI = EAutoPossessAI::Disabled;
	AIControllerClass = ADGAIController::StaticClass();

	bUseControllerRotationYaw = false;
    if (GetCharacterMovement())
    {
        GetCharacterMovement()->bUseControllerDesiredRotation = true;
        GetCharacterMovement()->RotationRate = FRotator(0.0f, 200.0f, 0.0f);
    }

	PrimaryActorTick.bCanEverTick = true;
}

void ADGEnemy::BeginPlay()
{
	Super::BeginPlay();
	
}

void ADGEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ADGEnemy::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

