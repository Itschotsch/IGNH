// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Items/Wearable.h"
#include "Weapon.generated.h"

/**
 * 
 */
UCLASS()
class IGNH_API AWeapon : public AWearable
{
	GENERATED_BODY()
	
public:
	// Sets default values for this actor's properties
	AWeapon();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called every frame
	virtual void Tick(float DeltaSeconds) override;
	
	
};
