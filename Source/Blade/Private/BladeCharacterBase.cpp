#include "BladeCharacterBase.h"
#include "BladeAttributeSet.h"

ABladeCharacterBase::ABladeCharacterBase()
{
	AttributeSet = CreateDefaultSubobject<UBladeAttributeSet>(TEXT("AttributeSet"));
}

void ABladeCharacterBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis(TEXT("MoveForward"), this, &ABladeCharacterBase::MoveForward);
	PlayerInputComponent->BindAxis(TEXT("MoveRight"), this, &ABladeCharacterBase::MoveRight);
	PlayerInputComponent->BindAxis(TEXT("LookUp"), this, &APawn::AddControllerPitchInput);
	PlayerInputComponent->BindAxis(TEXT("LookRight"), this, &APawn::AddControllerYawInput);
}

void ABladeCharacterBase::HandleDamage(float DamageAmount, const FHitResult& HitInfo, const FGameplayTagContainer& DamageTags, ABladeCharacterBase* InstigatorCharacter, AActor* DamageCauser)
{
	OnDamaged(DamageAmount, HitInfo, DamageTags, InstigatorCharacter, DamageCauser);
}

void ABladeCharacterBase::HandleHealthChanged(float DeltaValue, const FGameplayTagContainer& EventTags)
{
	OnHealthChanged(DeltaValue, EventTags);
}

float ABladeCharacterBase::GetHealth() const
{
	if (IsValid(AttributeSet))
	{
		return AttributeSet->GetHealth();
	}

	return 0.0f;
}

float ABladeCharacterBase::GetMaxHealth() const
{
	if (IsValid(AttributeSet))
	{
		return AttributeSet->GetMaxHealth();
	}

	return 0.0f;
}

void ABladeCharacterBase::MoveForward(float AxisValue)
{
	AddMovementInput(GetActorForwardVector(), AxisValue);
}

void ABladeCharacterBase::MoveRight(float AxisValue)
{
	AddMovementInput(GetActorRightVector(), AxisValue);
}
