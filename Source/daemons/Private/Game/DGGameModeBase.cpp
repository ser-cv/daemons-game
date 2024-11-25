// For Daemons and something else videogame purpose only

#include "Game/DGGameModeBase.h"
#include "Player/DGPlayerController.h"
#include "UsableActors/DGSpawner.h"
#include "EngineUtils.h"
#include "AIController.h"

DEFINE_LOG_CATEGORY_STATIC(DGGemeModeBase, All, All)

ADGGameModeBase::ADGGameModeBase()
{
    PlayerControllerClass = ADGPlayerController::StaticClass();
}

void ADGGameModeBase::InitGame(const FString& MapName, const FString& Options, FString& ErrorMessage)
{
    Super::InitGame(MapName, Options, ErrorMessage);

    FillSpawningActorsMap();
    GamePhase = EPhase::Phase_1;
    BeginNewPhase();
}

UClass* ADGGameModeBase::GetDefaultPawnClassForController_Implementation(AController* InController)
{
    if (InController && InController->IsA<AAIController>())
    {
        return PawnClass;
    }

    return Super::GetDefaultPawnClassForController_Implementation(InController);
}

AActor* ADGGameModeBase::ChoosePlayerStart_Implementation(AController* Player)
{
    return Super::ChoosePlayerStart_Implementation(Player);
}

void ADGGameModeBase::FailedToRestartPlayer(AController* NewPlayer)
{
    const float ResetDelay = 1.f;
    ResetPawnWithDelay(NewPlayer, ResetDelay);

    Super::FailedToRestartPlayer(NewPlayer);
}

void ADGGameModeBase::Killed(AController* VictimController, AController* KillerController)
{
    // update score for new phase
    TryToRespawn(VictimController);  // change to method with respawn delay
}

void ADGGameModeBase::FillSpawningActorsMap()
{
    for (const auto FoundActor : TActorRange<ADGSpawner>(GetWorld()))
    {
        UE_LOG(DGGemeModeBase, Display, TEXT("found actor: %s"), *FoundActor->GetName());
        if (!FoundActor) continue;
        if (FoundActor->WhichGamePhaseSelected() == EPhase::No_Phase)
        {
            UE_LOG(DGGemeModeBase, Display, TEXT("spawner: %s, has no selected phase"), *FoundActor->GetName());
        }
        SpawningActorsMap.FindOrAdd(FoundActor->WhichGamePhaseSelected()).Add(FoundActor);
    }
}

void ADGGameModeBase::TryToRespawn(AController* Controller)
{
    ResetPawn(Controller);
}

void ADGGameModeBase::ResetPawn(AController* VictimController)
{
    if (!VictimController) return;
    VictimController->UnPossess();

    if (GetWorld())
    {
        GetWorld()->GetTimerManager().ClearTimer(CheckSpawnerTimer);
    }

    const auto StartSpot = VictimController->IsA<APlayerController>() ? FindPlayerStart(VictimController, UEnum::GetValueAsString(GamePhase)) : GetSpawner(VictimController);

    RestartPlayerAtPlayerStart(VictimController, StartSpot);
}

void ADGGameModeBase::ResetPawnWithDelay(AController* VictimController, float Delay)
{
    if (!GetWorld()) return;
    auto TimerDelegate = FTimerDelegate::CreateUObject(this, &ADGGameModeBase::ResetPawn, VictimController);
    GetWorld()->GetTimerManager().SetTimer(CheckSpawnerTimer, TimerDelegate, Delay, false);
}

AActor* ADGGameModeBase::GetSpawner(AController* VictimController)
{
    if (!SpawningActorsMap.Contains(GamePhase)) return nullptr;

    AActor* BestSpawner{nullptr};
    const TArray<ADGSpawner*> SpawningActors{SpawningActorsMap.FindRef(GamePhase)};

    const auto RandomIndex = FMath::RandHelper(SpawningActors.Num());
    const auto Spawner = SpawningActors[RandomIndex];
    if (Spawner && Spawner->CanSpawn())
    {
        BestSpawner = Spawner;
        PawnClass = Spawner->ClassForSpawning();
    }

    if (!BestSpawner)
    {
        UE_LOG(DGGemeModeBase, Display, TEXT("can't find any spawner"));
        const float ResetDelay = 1.f;
        ResetPawnWithDelay(VictimController, ResetDelay);
    }

    return BestSpawner;
}

void ADGGameModeBase::BeginNewPhase()
{
    // update score
    // update info about enemies
    UpdateEnemiesNumberForPhase();
}

void ADGGameModeBase::UpdateEnemiesNumberForPhase()
{
    const int32 EnemiesPerPhase{10};  // todo > create struct with GamePhaseInfo
    auto EnemiesNeeded = EnemiesPerPhase - EnemyControllers.Num();
    if (!EnemiesNeeded) return;
    EnemiesNeeded > 0 ? AddAIController() : RemoveAIController();
}

void ADGGameModeBase::AddAIController()
{
    FActorSpawnParameters SpawnInfo;
    SpawnInfo.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
    const auto EnemyController = GetWorld()->SpawnActor<AAIController>(AIControllerClass, SpawnInfo);
    EnemyControllers.Add(EnemyController);
    ResetPawn(EnemyController);

    UpdateEnemiesNumberForPhase();
}

void ADGGameModeBase::RemoveAIController()
{
    const auto EnemyController = EnemyControllers.Pop(false);
    if (!EnemyController)
    {
        UpdateEnemiesNumberForPhase();
        return;
    }
    const auto EnemyPawn = EnemyController->GetPawn();
    EnemyController->UnPossess();
    if (EnemyPawn)
    {
        EnemyPawn->Destroy();
    }
    EnemyController->Destroy();

    UpdateEnemiesNumberForPhase();
}
