#include "BladeAIController.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISense_Sight.h"

ABladeAIController::ABladeAIController()
{
	AIPerceptionComponent = CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("AIPerception"));
	SetPerceptionComponent(*AIPerceptionComponent);
}

void ABladeAIController::PauseLogic(const FString& Reason)
{
	GetBrainComponent()->PauseLogic(Reason);
}

void ABladeAIController::ResumeLogic(const FString& Reason)
{
	GetBrainComponent()->ResumeLogic(Reason);
}

void ABladeAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	if (ensureMsgf(BehaviorTree, TEXT("Please setup the Behavior tree in Enemy Character")))
	{
		RunBehaviorTree(BehaviorTree);
	}

	AIPerceptionComponent->OnTargetPerceptionUpdated.AddDynamic(this, &ABladeAIController::UpdateTargetActor);
}

void ABladeAIController::OnUnPossess()
{
	Super::OnUnPossess();

	if (AIPerceptionComponent &&
		AIPerceptionComponent->OnTargetPerceptionUpdated.Contains(this, TEXT("UpdateTargetActor")))
	{
		AIPerceptionComponent->OnTargetPerceptionUpdated.RemoveDynamic(this, &ABladeAIController::UpdateTargetActor);
	}
}

void ABladeAIController::UpdateTargetActor(AActor* Actor, FAIStimulus Stimulus)
{
	TSubclassOf<UAISense> SenseClass = UAIPerceptionSystem::GetSenseClassForStimulus(GetWorld(), Stimulus);

	if (SenseClass == UAISense_Sight::StaticClass())
	{
		if (Stimulus.WasSuccessfullySensed())
		{
			GetBlackboardComponent()->SetValueAsObject(TEXT("TargetActor"), Actor);
		}
		else
		{
			GetBlackboardComponent()->ClearValue(TEXT("TargetActor"));
			GetBlackboardComponent()->SetValueAsVector(TEXT("PatrolLocation"), Actor->GetActorLocation());
		}
	}
}
