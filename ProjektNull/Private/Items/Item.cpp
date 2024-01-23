// Fill out your copyright notice in the Description page of Project Settings.

#include "Items/Item.h"
#include "DrawDebugHelpers.h"
#include "ProjektNull/DebugMacros.h"


// Sets default values
AItem::AItem()
{
	PrimaryActorTick.bCanEverTick = true;

	ItemMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ItemMesh"));
	RootComponent = ItemMesh;
}

void AItem::BeginPlay()
{
	Super::BeginPlay();

	const FString Name = GetName();
	UE_LOG(LogTemp, Warning, TEXT("%s is alive!"), *Name);
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(1, 20.f, FColor::Red,
		                                 FString::Printf(TEXT("%s is alive!"), *Name));
	}
}

float AItem::TransformSin()
{
	return Amplitude * FMath::Sin(RunningTime * TimeConstant);
}

float AItem::TransformCos()
{
	return Amplitude * FMath::Cos(RunningTime * TimeConstant);
}

void AItem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	RunningTime += DeltaTime;
}
