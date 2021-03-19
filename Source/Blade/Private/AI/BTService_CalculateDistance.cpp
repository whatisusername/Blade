#include "BTService_CalculateDistance.h"
#include "BladeAIController.h"
#include "BehaviorTree/BlackboardComponent.h"

UBTService_CalculateDistance::UBTService_CalculateDistance(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	NodeName = TEXT("Calculate Distance to Target");
}

void UBTService_CalculateDistance::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	UBlackboardComponent* BlackboardComponent = OwnerComp.GetBlackboardComponent();
	AActor* Target = Cast<AActor>(BlackboardComponent->GetValueAsObject(TargetKey.SelectedKeyName));
	if (Target == nullptr)
	{
		return;
	}

	ABladeAIController* Controller = Cast<ABladeAIController>(OwnerComp.GetOwner());
	if (Controller)
	{
		float Distance = Target->GetDistanceTo(Controller->GetPawn());
		BlackboardComponent->SetValueAsFloat(DistanceKey.SelectedKeyName, Distance);
	}
}
