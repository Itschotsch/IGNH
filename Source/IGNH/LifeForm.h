// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Character.h"
#include "BaseItem.h"
#include "LifeForm.generated.h"


// Character state enum
UENUM(BlueprintType)
enum class EActionEnum : uint8
{
	AE_Nothing			UMETA(DisplayName = "Nothing"),
	AE_Attacking		UMETA(DisplayName = "Attacking"),
	AE_AttackBlocked	UMETA(DisplayName = "AttackBlocked"),
	AE_Blocking			UMETA(DisplayName = "Blocking"),
	AE_BlockedAttack	UMETA(DisplayName = "BlockedAttack")

};

UCLASS()
class IGNH_API ALifeForm : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ALifeForm();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called every frame
	virtual void Tick(float DeltaSeconds) override;

	//Handles input for moving forward and backward.
	UFUNCTION()
		void MoveForward(float Value);

	// Handles input for moving right and left.
	UFUNCTION()
		void MoveRight(float Value);

	// Set jump flag when key is pressed.
	UFUNCTION()
		void StartJump();

	// Clears jump flag when key is released.
	UFUNCTION()
		void StopJump();

	// Sets equiped armor and sets the master pose for the animation
	UFUNCTION()
		void AddEquipment(USkeletalMeshComponent *TargetMesh, USkeletalMesh *ItemToAdd);

	// Equips and unequips weapons on either the right or the left slot
	UFUNCTION()
		void EquipWeapon(bool bRightSlot, bool bEquip, TSubclassOf<AActor> WeaponClass);


	/*-------------------------------------------------
	-------------    Variables    ---------------------
	-------------------------------------------------*/


	// Default collision boxes
	// Head
	UPROPERTY(VisibleDefaultsOnly, Category = Collision)
		UCapsuleComponent* Head1;
	UPROPERTY(VisibleDefaultsOnly, Category = Collision)
		UBoxComponent* Head2;

	// Torso
	UPROPERTY(VisibleDefaultsOnly, Category = Collision)
		UBoxComponent* Torso1;
	UPROPERTY(VisibleDefaultsOnly, Category = Collision)
		UBoxComponent* Torso2;

	// Arms
	UPROPERTY(VisibleDefaultsOnly, Category = Collision)
		UCapsuleComponent* Arm1;
	UPROPERTY(VisibleDefaultsOnly, Category = Collision)
		UCapsuleComponent* Arm2;
	UPROPERTY(VisibleDefaultsOnly, Category = Collision)
		UCapsuleComponent* Arm3;
	UPROPERTY(VisibleDefaultsOnly, Category = Collision)
		UCapsuleComponent* Arm4;

	// Legs
	UPROPERTY(VisibleDefaultsOnly, Category = Collision)
		UCapsuleComponent* Leg1;
	UPROPERTY(VisibleDefaultsOnly, Category = Collision)
		UCapsuleComponent* Leg2;
	UPROPERTY(VisibleDefaultsOnly, Category = Collision)
		UCapsuleComponent* Leg3;
	UPROPERTY(VisibleDefaultsOnly, Category = Collision)
		UCapsuleComponent* Leg4;

	/*-------------------------------------------------
	-------------------------------------------------*/

	// Armor slots
	UPROPERTY(VisibleDefaultsOnly, Category = Equipment)
		USkeletalMeshComponent* Helmet;
	UPROPERTY(VisibleDefaultsOnly, Category = Equipment)
		USkeletalMeshComponent* ChestArmor;
	UPROPERTY(VisibleDefaultsOnly, Category = Equipment)
		USkeletalMeshComponent* LegArmor;
	UPROPERTY(VisibleDefaultsOnly, Category = Equipment)
		USkeletalMeshComponent* UpperSuit;
	UPROPERTY(VisibleDefaultsOnly, Category = Equipment)
		USkeletalMeshComponent* LowerSuit;
	UPROPERTY(VisibleDefaultsOnly, Category = Equipment)
		USkeletalMeshComponent* Boots;

	// Weapon slots
	UPROPERTY(VisibleDefaultsOnly, Category = Equipment)
		UChildActorComponent* RightWeapon;
	UPROPERTY(VisibleDefaultsOnly, Category = Equipment)
		UChildActorComponent* LeftWeapon;

	/*-------------------------------------------------
	-------------------------------------------------*/

	// Mouseposition, angle and vector length
	UPROPERTY()
		FVector2D MousePosition;
	UPROPERTY()
		float DrawAngle;
	UPROPERTY()
		float VectorLength;
	UPROPERTY()
		FVector2D ArtificialMouse;
	UPROPERTY()
		float ArtificialMouseAngle;
	UPROPERTY()
		float ArificialVectorLength;

	/*-------------------------------------------------
	-------------------------------------------------*/

	// Character stats
	UPROPERTY(VisibleDefaultsOnly, Category = Stats)
		FString Name;
	UPROPERTY(VisibleDefaultsOnly, Category = Stats)
		float MaxHealth;
	UPROPERTY()
		float CurrentHealth;
	UPROPERTY(VisibleDefaultsOnly, Category = Stats)
		float HealthRegen;
	UPROPERTY(VisibleDefaultsOnly, Category = Stats)
		float Stamina;
	UPROPERTY()
		float CurrentStamina;
	UPROPERTY(VisibleDefaultsOnly, Category = Stats)
		float StaminaRegen;
	UPROPERTY(VisibleDefaultsOnly, Category = Stats)
		float Power;
	UPROPERTY(VisibleDefaultsOnly, Category = Stats)
		float Agility;
	UPROPERTY(VisibleDefaultsOnly, Category = Stats)
		float Defense;
	UPROPERTY(VisibleDefaultsOnly, Category = Stats)
		float BaseMovespeed;
	UPROPERTY()
		float CurrentMovespeed;
	UPROPERTY(VisibleDefaultsOnly, Category = Stats)
		float BaseWeight;
	UPROPERTY()
		float CurrentWeight;
	UPROPERTY(VisibleDefaultsOnly, Category = Stats)
		float Level;

	// Character state
	UPROPERTY()
		EActionEnum ActionEnum;


};
