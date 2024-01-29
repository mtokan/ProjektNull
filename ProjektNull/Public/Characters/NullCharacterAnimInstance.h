// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CharacterState.h"
#include "Animation/AnimInstance.h"
#include "NullCharacterAnimInstance.generated.h"

class UCharacterMovementComponent;
class ANullCharacter;
/**
 * 
 */
UCLASS()
class PROJEKTNULL_API UNullCharacterAnimInstance : public UAnimInstance
{
	GENERATED_BODY()

public:
	virtual void NativeInitializeAnimation() override;
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

	UPROPERTY(BlueprintReadOnly)
	ANullCharacter* NullCharacter;

	UPROPERTY(BlueprintReadOnly, Category = Movement)
	UCharacterMovementComponent* MovementComponent;

	UPROPERTY(BlueprintReadOnly, Category = Movement)
	float GroundSpeed;

	UPROPERTY(BlueprintReadOnly, Category = Movement)
	bool IsFalling;

	UPROPERTY(BlueprintReadOnly, Category = "Movement | Character State")
	ECharacterState CharacterState;
};
