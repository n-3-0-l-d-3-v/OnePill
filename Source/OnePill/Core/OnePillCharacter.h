#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "InputActionValue.h"
#include "OnePillCharacter.generated.h"

class UCameraComponent;
class UInputMappingContext;
class UInputAction;

/**
 * Pre-Pill first-person character: standard walk/look controls. Post-Pill behavior
 * modifications are applied by the Living Rule Graph via components, not by subclassing.
 */
UCLASS()
class ONEPILL_API AOnePillCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	AOnePillCharacter();

protected:
	virtual void BeginPlay() override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void Move(const FInputActionValue& Value);
	void Look(const FInputActionValue& Value);

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "OnePill|Camera")
	TObjectPtr<UCameraComponent> FirstPersonCamera;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "OnePill|Input")
	TObjectPtr<UInputMappingContext> DefaultMappingContext;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "OnePill|Input")
	TObjectPtr<UInputAction> MoveAction;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "OnePill|Input")
	TObjectPtr<UInputAction> LookAction;
};
