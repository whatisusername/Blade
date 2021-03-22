#include "AnimNotifyState_BlockInput.h"
#include "BladeCharacterBase.h"
#include "BladePlayerControllerBase.h"

void UAnimNotifyState_BlockInput::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration)
{
	ABladeCharacterBase* Character = Cast<ABladeCharacterBase>(MeshComp->GetOwner());
	if (Character)
	{
		ABladePlayerControllerBase* Controller = Character->GetController<ABladePlayerControllerBase>();
		if (Controller)
		{
			Character->DisableInput(Controller);
		}
	}
}

void UAnimNotifyState_BlockInput::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	ABladeCharacterBase* Character = Cast<ABladeCharacterBase>(MeshComp->GetOwner());
	if (Character)
	{
		ABladePlayerControllerBase* Controller = Character->GetController<ABladePlayerControllerBase>();
		if (Controller)
		{
			Character->EnableInput(Controller);
		}
	}
}
