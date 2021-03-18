#include "BladeAnimNotify_WeaponHit.h"
#include "BladeCharacterBase.h"

void UBladeAnimNotify_WeaponHit::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	Super::Notify(MeshComp, Animation);

	ABladeCharacterBase* Character = Cast<ABladeCharacterBase>(MeshComp->GetOwner());
	if (Character)
	{
		Character->Attack(WeaponHitTag);
	}
}
