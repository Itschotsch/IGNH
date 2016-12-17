// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "LifeForm.h"
#include "PlayerCharacter.generated.h"

/**
*
*/
UCLASS()
class IGNH_API APlayerCharacter : public ALifeForm
{
	GENERATED_BODY()
public:

	// Sets default values for this character's properties
	APlayerCharacter();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called every frame
	virtual void Tick(float DeltaSeconds) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	// Calculate the position of the mouse and articial-mouse 
	UFUNCTION()
		FVector2D CenterCoordinates(float LocationX, float LocationY);
	UFUNCTION()
		float Vector2DAngle(FVector2D Vector);
	UFUNCTION()
		void CalculateMouse();
	UFUNCTION()
		void CalculateArtificialMouse();

	// Sets attack and block mode
	UFUNCTION()
		void AttackModeEnter();
	UFUNCTION()
		void AttackModeEnd();
	UFUNCTION()
		void BlockModeEnter();
	UFUNCTION()
		void BlockModeEnd();

	// Handles mouse clicks
	UFUNCTION()
		void RightButtonPressed();
	UFUNCTION()
		void RightButtonReleased();
	UFUNCTION()
		void LeftButtonPressed();
	UFUNCTION()
		void LeftButtonReleased();
	// Decides what to do 
	UFUNCTION()
		void OnMouseClick(bool bRight);
	UFUNCTION()
		void OnMouseRelease(bool bRight);


	/*-------------------------------------------------
	-------------    Variables    ---------------------
	-------------------------------------------------*/

	// Camera
	UPROPERTY(VisibleAnywhere)
		UCameraComponent* FPCameraComponent;
	// First-person mesh, visible only to the owning player.
	UPROPERTY(VisibleDefaultsOnly, Category = Mesh)
		USkeletalMeshComponent* FPMesh;

	UPROPERTY()
		bool bAttackMode;
	UPROPERTY()
		bool bBlockMode;

};
