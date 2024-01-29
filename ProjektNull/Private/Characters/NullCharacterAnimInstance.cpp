// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/NullCharacterAnimInstance.h"
#include "Characters/NullCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/KismetMathLibrary.h"

void UNullCharacterAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();

	NullCharacter = Cast<ANullCharacter>(TryGetPawnOwner());
	if (NullCharacter)
	{
		MovementComponent = NullCharacter->GetCharacterMovement();
	}
}

void UNullCharacterAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	if (MovementComponent)
	{
		GroundSpeed = UKismetMathLibrary::VSizeXY(MovementComponent->Velocity);
		IsFalling = MovementComponent->IsFalling();
		CharacterState = NullCharacter->GetCharacterState();
	}
}
