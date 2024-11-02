// For Daemons and something else videogame purpose only


#include "AI/Tasks/DGBTTaskReportAboutEnemy.h"
#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Perception/AISense_Team.h"
#include "Perception/AIPerceptionSystem.h"
#include "Perception/AIPerceptionComponent.h"

UDGBTTaskReportAboutEnemy::UDGBTTaskReportAboutEnemy() 
{
    NodeName = "Report Teammate About Enemy";
}

EBTNodeResult::Type UDGBTTaskReportAboutEnemy::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
    const auto Blackboard = OwnerComp.GetBlackboardComponent();
    if (!Blackboard) return EBTNodeResult::Failed;

    const auto AIController = OwnerComp.GetAIOwner();
    if (!AIController) return EBTNodeResult::Failed;

    const auto PerceptionComponent = AIController->PerceptionComponent;
    if (!PerceptionComponent) return EBTNodeResult::Failed;

    const auto EnemyActor = Cast<AActor>(Blackboard->GetValueAsObject(EnemyActorKey.SelectedKeyName));

    const auto PerceptionSystem = UAIPerceptionSystem::GetCurrent(GetWorld());
	
    if (!PerceptionSystem) EBTNodeResult::Failed;
    FAITeamStimulusEvent Event(AIController->GetPawn(), EnemyActor, PerceptionComponent->GetActorLocation(*EnemyActor), ReportRange);
    PerceptionSystem->OnEvent(Event);
    return EBTNodeResult::Succeeded;
}
