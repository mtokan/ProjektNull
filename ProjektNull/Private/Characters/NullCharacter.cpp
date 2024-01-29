// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/NullCharacter.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Items/Weapons/Weapon.h"
#include "Pawns/Bird.h"

ANullCharacter::ANullCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.f, 400.f, 0.f);

	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArm->SetupAttachment(GetRootComponent());
	SpringArm->bUsePawnControlRotation = true;

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(SpringArm);
}

void ANullCharacter::BeginPlay()
{
	Super::BeginPlay();

	if (const APlayerController* PlayerController = Cast<APlayerController>(GetController()))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<
			UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(NullCharacterMappingContext, 0);
		}
	}
}

void ANullCharacter::Move(const FInputActionValue& Value)
{
	if (const FVector2d MovementVector = Value.Get<FVector2d>(); GetController())
	{
		const FRotator Rotation = GetController()->GetControlRotation();
		const FRotator YawRotation(0.f, Rotation.Yaw, 0.f);
		const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

		AddMovementInput(ForwardDirection, MovementVector.Y);
		AddMovementInput(RightDirection, MovementVector.X);
	}
}

void ANullCharacter::Look(const FInputActionValue& Value)
{
	if (const FVector2d LookAxisVector = Value.Get<FVector2d>(); GetController())
	{
		AddControllerPitchInput(LookAxisVector.Y);
		AddControllerYawInput(LookAxisVector.X);
	}
}

void ANullCharacter::Equip()
{
	if(AWeapon* OverlappingWeapon = Cast<AWeapon>(OverlappingItem))
	{
		OverlappingWeapon->Equip(GetMesh(),FName("RightHandSocket"));
		CharacterState = ECharacterState::ECS_EquippedOneHandedWeapon;
	}
}

void ANullCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ANullCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent))
	{
		EnhancedInputComponent->BindAction(MovementAction, ETriggerEvent::Triggered, this, &ANullCharacter::Move);
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &ANullCharacter::Look);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Triggered, this, &ACharacter::Jump);
		EnhancedInputComponent->BindAction(EquipAction, ETriggerEvent::Triggered, this, &ANullCharacter::Equip);
	}
}
