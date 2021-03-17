#include "BladeAnimNotifyState_BlockInput.h"
#include "BladeCharacterBase.h"
#include "BladePlayerControllerBase.h"

void UBladeAnimNotifyState_BlockInput::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration)
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

void UBladeAnimNotifyState_BlockInput::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
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
