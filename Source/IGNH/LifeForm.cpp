// Fill out your copyright notice in the Description page of Project Settings.

#include "IGNH.h"
#include "LifeForm.h"
#include "Kismet/GameplayStatics.h"


// Sets default values
ALifeForm::ALifeForm()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it
	PrimaryActorTick.bCanEverTick = true;

	// Create equipment slots
	Helmet = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Helmet"));
	ChestArmor = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("ChestArmor"));
	LegArmor = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("LegArmor"));
	UpperSuit = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("UpperSuit"));
	LowerSuit = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("LowerSuit"));
	Boots = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Boots"));

	// Attaches the equipment slots to the mesh
	Helmet->AttachTo(GetMesh());
	ChestArmor->AttachTo(GetMesh());
	LegArmor->AttachTo(GetMesh());
	UpperSuit->AttachTo(GetMesh());
	LowerSuit->AttachTo(GetMesh());
	Boots->AttachTo(GetMesh());

	//Create weapon child actors
	RightWeapon = CreateDefaultSubobject<UChildActorComponent>(TEXT("RightWeapon"));
	LeftWeapon = CreateDefaultSubobject<UChildActorComponent>(TEXT("LeftWeapon"));

	// Attaches the weapon slots to the mesh
	RightWeapon->AttachTo(GetMesh());
	LeftWeapon->AttachTo(GetMesh());

}

// Called when the game starts or when spawned
void ALifeForm::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void ALifeForm::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Function declaration

void ALifeForm::MoveForward(float Value)
{
	// Find out wich way is "forward" and record that the player wants to move that way
	FVector Direction = GetActorForwardVector();
	AddMovementInput(Direction, Value);
}

void ALifeForm::MoveRight(float Value)
{
	// Find out wich way is "right" and record that the player wants to move that way
	FVector Direction = FRotationMatrix(Controller->GetControlRotation()).GetScaledAxis(EAxis::Y);
	AddMovementInput(Direction, Value);
}

void ALifeForm::StartJump()
{
	bPressedJump = true;
}

void ALifeForm::StopJump()
{
	bPressedJump = false;
}

void ALifeForm::AddEquipment(USkeletalMeshComponent *TargetMesh, USkeletalMesh *ItemToAdd)
{
	if (IsValid(ItemToAdd))
	{
		USkeletalMeshComponent *Mesh = GetMesh();
		TargetMesh->SetSkeletalMesh(ItemToAdd, true);
		TargetMesh->SetMasterPoseComponent(Mesh);
	}
}

void ALifeForm::EquipWeapon(bool bRightSlot, bool bEquip, TSubclassOf<AActor> WeaponClass)
{
	RightWeapon->SetChildActorClass(WeaponClass);
}
