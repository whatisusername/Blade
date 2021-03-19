#include "BTTask_Attack.h"
#include "BladeAIController.h"
#include "BladeEnemyCharacter.h"

UBTTask_Attack::UBTTask_Attack(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	NodeName = TEXT("Attack");
}

EBTNodeResult::Type UBTTask_Attack::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	ABladeAIController* Controller = Cast<ABladeAIController>(OwnerComp.GetOwner());
	if (Controller == nullptr)
	{
		return EBTNodeResult::Failed;
	}

	ABladeEnemyCharacter* Character = Controller->GetPawn<ABladeEnemyCharacter>();
	if (Character == nullptr)
	{
		return EBTNodeResult::Failed;
	}

	if (Character->CanUseAbility() && !Character->IsUsingMelee())
	{
		bool bActivateSuccess = Character->ActivateAbilitiesWithTags(AttackTags);
		return bActivateSuccess ? EBTNodeResult::Succeeded : EBTNodeResult::Failed;
	}

	return EBTNodeResult::Failed;
}
