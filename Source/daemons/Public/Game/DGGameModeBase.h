// For Daemons and something else videogame purpose only

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "DGCoreTypes.h"
#include "DGGameModeBase.generated.h"

class ADGSpawner;
class AAIController;

UCLASS()
class DAEMONS_API ADGGameModeBase : public AGameModeBase
{
    GENERATED_BODY()

public:
    ADGGameModeBase();

    virtual void InitGame(const FString& MapName, const FString& Options, FString& ErrorMessage) override;
    virtual UClass* GetDefaultPawnClassForController_Implementation(AController* InController) override;
    virtual AActor* ChoosePlayerStart_Implementation(AController* Player) override;
    virtual void FailedToRestartPlayer(AController* NewPlayer);

    void Killed(AController* VictimController, AController* KillerController);

protected:
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
    TSubclassOf<AAIController> AIControllerClass;

private:
    EPhase GamePhase{EPhase::No_Phase};
    TMap<EPhase, TArray<ADGSpawner*>> SpawningActorsMap;
    TArray<AAIController*> EnemyControllers;
    FTimerHandle CheckSpawnerTimer;
    TSubclassOf<APawn> PawnClass;

    void FillSpawningActorsMap();
    void TryToRespawn(AController* Controller);
    void ResetPawn(AController* VictimController);
    void ResetPawnWithDelay(AController* VictimController, float Delay);
    AActor* GetSpawner(AController* VictimController);

    void BeginNewPhase();
    void UpdateEnemiesNumberForPhase();
    void AddAIController();
    void RemoveAIController();
};