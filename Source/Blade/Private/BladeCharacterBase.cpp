#include "BladeCharacterBase.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "BladeAbilitySystemComponent.h"
#include "BladeAttributeSet.h"
#include "BladeGameplayAbility.h"
#include "GameplayEffect.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"

ABladeCharacterBase::ABladeCharacterBase(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	AbilitySystemComponent = ObjectInitializer.CreateDefaultSubobject<UBladeAbilitySystemComponent>(this, TEXT("AbilitySystemComponent"));
	AbilitySystemComponent->SetIsReplicated(true);

	AttributeSet = ObjectInitializer.CreateDefaultSubobject<UBladeAttributeSet>(this, TEXT("AttributeSet"));
}

void ABladeCharacterBase::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	if (AbilitySystemComponent)
	{
		AbilitySystemComponent->InitAbilityActorInfo(this, this);
		AddStartupGameplayEffects();
		GrantAbilities();
	}
}

void ABladeCharacterBase::OnRep_PlayerState()
{
	Super::OnRep_PlayerState();

	if (AbilitySystemComponent)
	{
		AbilitySystemComponent->InitAbilityActorInfo(this, this);
		AddStartupGameplayEffects();
	}

	BindAbilityInput();
}

void ABladeCharacterBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis(TEXT("MoveForward"), this, &ABladeCharacterBase::MoveForward);
	PlayerInputComponent->BindAxis(TEXT("MoveRight"), this, &ABladeCharacterBase::MoveRight);
	PlayerInputComponent->BindAxis(TEXT("LookUp"), this, &APawn::AddControllerPitchInput);
	PlayerInputComponent->BindAxis(TEXT("LookRight"), this, &APawn::AddControllerYawInput);

	BindAbilityInput();
}

UAbilitySystemComponent* ABladeCharacterBase::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

void ABladeCharacterBase::HandleDamage(float DamageAmount, const FHitResult& HitInfo, const FGameplayTagContainer& DamageTags, ABladeCharacterBase* InstigatorCharacter, AActor* DamageCauser)
{
	OnDamaged(DamageAmount, HitInfo, DamageTags, InstigatorCharacter, DamageCauser);
}

void ABladeCharacterBase::HandleHealthChanged(float DeltaValue, const FGameplayTagContainer& EventTags)
{
	OnHealthChanged(DeltaValue, EventTags);
}

bool ABladeCharacterBase::Attack(const FGameplayTag& GameplayTag)
{
	FVector Location = GetMesh()->GetSocketLocation(AttackSocketName);
	TArray<TEnumAsByte<EObjectTypeQuery>> Types{ UEngineTypes::ConvertToObjectType(ECollisionChannel::ECC_Pawn) };
	TArray<AActor*> IgnoreActors{ this };
	TArray<AActor*> OverlapActors;
	const float Radius = 30.0f;

	bool bHasOverlap = UKismetSystemLibrary::SphereOverlapActors(GetWorld(), Location, Radius, Types, StaticClass(), IgnoreActors, OverlapActors);
	if (bHasOverlap)
	{
		FGameplayEventData Payload;
		Payload.Instigator = GetInstigator();
		Payload.Target = OverlapActors[0];
		UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(GetInstigator(), GameplayTag, Payload);

		return true;
	}
	return false;
}

int32 ABladeCharacterBase::GetCharacterLevel() const
{
	return 1;
}

bool ABladeCharacterBase::IsAlive() const
{
	return GetHealth() > 0;
}

bool ABladeCharacterBase::CanUseAbility() const
{
	return IsAlive() && !UGameplayStatics::IsGamePaused(GetWorld());
}

bool ABladeCharacterBase::IsUsingMelee() const
{
	TArray<UBladeGameplayAbility*> ActiveAbilities;
	GetActiveAbilitiesWithTags(MeleeTags, ActiveAbilities);
	return ActiveAbilities.Num() > 0;
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

void ABladeCharacterBase::AddStartupGameplayEffects()
{
	check(AbilitySystemComponent);

	for (TSubclassOf<UGameplayEffect> GameplayEffect : DefaultEffects)
	{
		FGameplayEffectContextHandle ContextHandle = AbilitySystemComponent->MakeEffectContext();
		ContextHandle.AddSourceObject(this);

		FGameplayEffectSpecHandle SpecHandle = AbilitySystemComponent->MakeOutgoingSpec(GameplayEffect, GetCharacterLevel(), ContextHandle);
		if (SpecHandle.IsValid())
		{
			FActiveGameplayEffectHandle EffectHandle = AbilitySystemComponent->ApplyGameplayEffectSpecToTarget(*SpecHandle.Data.Get(), AbilitySystemComponent);
		}
	}
}

void ABladeCharacterBase::GrantAbilities()
{
	check(AbilitySystemComponent);

	if (bAbilitiesInitialized || !HasAuthority())
	{
		return;
	}

	for (const TSubclassOf<UBladeGameplayAbility>& GameAbility : DefaultAbilities)
	{
		AbilitySystemComponent->GiveAbility(
			FGameplayAbilitySpec(GameAbility, 1, static_cast<int32>(GameAbility.GetDefaultObject()->GetAbilityInputId()), this)
		);
	}

	bAbilitiesInitialized = true;
}

void ABladeCharacterBase::BindAbilityInput()
{
	check(InputComponent);

	const FGameplayAbilityInputBinds Binds(TEXT("Confirm"),
										   TEXT("Cancel"),
										   TEXT("EBladeAbilityInputId"),
										   static_cast<int32>(EBladeAbilityInputId::Confirm),
										   static_cast<int32>(EBladeAbilityInputId::Cancel));

	AbilitySystemComponent->BindAbilityActivationToInputComponent(InputComponent, Binds);
}

bool ABladeCharacterBase::ActivateAbilitiesWithTags(FGameplayTagContainer AbilityTags, bool bAllowRemoteActivation)
{
	if (AbilitySystemComponent)
	{
		return AbilitySystemComponent->TryActivateAbilitiesByTag(AbilityTags, bAllowRemoteActivation);
	}
	return false;
}

void ABladeCharacterBase::GetActiveAbilitiesWithTags(FGameplayTagContainer AbilityTags, TArray<UBladeGameplayAbility*>& ActiveAbilities) const
{
	check(AbilitySystemComponent);
	AbilitySystemComponent->GetActiveAbilitiesWithTags(AbilityTags, ActiveAbilities);
}
