#include "BladeAnimNotifyState_BlockInput.h"
#include "BladeCharacterBase.h"
#include "GameFramework/PlayerController.h"

void UBladeAnimNotifyState_BlockInput::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration)
{
	ABladeCharacterBase* Character = Cast<ABladeCharacterBase>(MeshComp->GetOwner());
	if (Character)
	{

		APlayerController* Controller = Character->GetController<APlayerController>();
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
		APlayerController* Controller = Character->GetController<APlayerController>();
		if (Controller)
		{
			Character->EnableInput(Controller);
		}
	}
}
