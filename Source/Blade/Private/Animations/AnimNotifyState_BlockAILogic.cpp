#include "AnimNotifyState_BlockAILogic.h"
#include "BladeAIController.h"
#include "BladeCharacterBase.h"

void UAnimNotifyState_BlockAILogic::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration)
{
	ABladeCharacterBase* Character = Cast<ABladeCharacterBase>(MeshComp->GetOwner());
	if (Character)
	{
		ABladeAIController* Controller = Character->GetController<ABladeAIController>();
		if (Controller)
		{
			Controller->PauseLogic(TEXT("Playing Montage"));
		}
	}
}

void UAnimNotifyState_BlockAILogic::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	ABladeCharacterBase* Character = Cast<ABladeCharacterBase>(MeshComp->GetOwner());
	if (Character)
	{
		ABladeAIController* Controller = Character->GetController<ABladeAIController>();
		if (Controller)
		{
			Controller->ResumeLogic(TEXT("Montage was finish played"));
		}
	}
}
