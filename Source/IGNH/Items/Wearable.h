// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "BaseItem.h"
#include "Wearable.generated.h"

// Wearable type enum
UENUM(BlueprintType)
enum class EWearableEnum : uint8
{
	WE_Head				UMETA(DisplayName = "Head"),
	WE_Chest			UMETA(DisplayName = "Chest"),
	WE_Arms				UMETA(DisplayName = "Arms"),
	WE_Legs				UMETA(DisplayName = "Legs"),
	WE_OneHandWeapon	UMETA(DisplayName = "OneHandWeapon"),
	WE_TwoHandWeapon	UMETA(DisplayName = "TwoHandWeapon")
};

UCLASS()
class IGNH_API AWearable : public ABaseItem
{
	GENERATED_BODY()
	
public:
	// Sets default values for this actor's properties
	AWearable();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called every frame
	virtual void Tick(float DeltaSeconds) override;

	// Variables for stats
	UPROPERTY(VisibleDefaultsOnly, Category = Stats)
		float Health;
	UPROPERTY(VisibleDefaultsOnly, Category = Stats)
		float HealthRegen;
	UPROPERTY(VisibleDefaultsOnly, Category = Stats)
		float Stamina;
	UPROPERTY(VisibleDefaultsOnly, Category = Stats)
		float StaminaDrain;
	UPROPERTY(VisibleDefaultsOnly, Category = Stats)
		float Power;
	UPROPERTY(VisibleDefaultsOnly, Category = Stats)
		float Agility;
	UPROPERTY(VisibleDefaultsOnly, Category = Stats)
		float Defense;
	UPROPERTY(VisibleDefaultsOnly, Category = Stats)
		EWearableEnum WearableType;

	// Functions
	UFUNCTION()
		void Equip();
	UFUNCTION()
		void UnEquip();

};
