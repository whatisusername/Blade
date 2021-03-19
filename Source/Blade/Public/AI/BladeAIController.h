#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "Perception/AIPerceptionTypes.h"
#include "BladeAIController.generated.h"

class UBehaviorTree;
class UAIPerceptionComponent;

UCLASS()
class BLADE_API ABladeAIController : public AAIController
{
	GENERATED_BODY()

public:
	ABladeAIController();

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "AI")
	UAIPerceptionComponent* AIPerceptionComponent;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "AI")
	UBehaviorTree* BehaviorTree;

	virtual void OnPossess(APawn* InPawn) override;
	virtual void OnUnPossess() override;

	UFUNCTION()
	virtual void UpdateTargetActor(AActor* Actor, FAIStimulus Stimulus);
};
