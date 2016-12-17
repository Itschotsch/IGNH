// Fill out your copyright notice in the Description page of Project Settings.

#include "IGNH.h"
#include "PlayerCharacter.h"
#include "LifeForm.h"


// Sets default values
APlayerCharacter::APlayerCharacter()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it
	PrimaryActorTick.bCanEverTick = true;

	// Create a first person camera component.
	FPCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("FirstPersonCamera"));
	// Attach the camera component to our capsule component
	FPCameraComponent->AttachTo(GetCapsuleComponent());
	// Position the camera at eye height.
	FPCameraComponent->SetRelativeLocation(FVector(0.0f, 0.0f, BaseEyeHeight));
	// Allow pawn to control camera rotation.
	FPCameraComponent->bUsePawnControlRotation = true;

	// Create a first person mesh component for the owning player.
	FPMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("FPMesh"));
	// Only the owning player sees this mesh.
	FPMesh->SetOnlyOwnerSee(true);
	// Attach the FP mesh to the FPS camera
	FPMesh->AttachTo(FPCameraComponent);
	// Disable some enviromental shadowing to preserve the illusion of having a single mesh.
	FPMesh->bCastDynamicShadow = false;
	FPMesh->CastShadow = false;
	// The owning player doesn't see the regular mesh.
	GetMesh()->SetOwnerNoSee(true);

}

// Called when the game starts or when spawned
void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void APlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (bBlockMode)
	{
		CalculateMouse();
		CalculateArtificialMouse();
	}

}

// Called to bind functionality to input
void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	// Set up movement bindings
	InputComponent->BindAxis("MoveForward", this, &ALifeForm::MoveForward);
	InputComponent->BindAxis("MoveRight", this, &ALifeForm::MoveRight);

	// Set up look input
	InputComponent->BindAxis("Turn", this, &ALifeForm::AddControllerYawInput);
	InputComponent->BindAxis("LookUp", this, &ALifeForm::AddControllerPitchInput);

	// Set up action bindings
	InputComponent->BindAction("Jump", IE_Pressed, this, &ALifeForm::StartJump);
	InputComponent->BindAction("Jump", IE_Released, this, &ALifeForm::StopJump);

	// Set up mouse input
	InputComponent->BindAction("RightHand", IE_Pressed, this, &APlayerCharacter::RightButtonPressed);
	InputComponent->BindAction("RightHand", IE_Released, this, &APlayerCharacter::RightButtonReleased);
	InputComponent->BindAction("LeftHand", IE_Pressed, this, &APlayerCharacter::LeftButtonPressed);
	InputComponent->BindAction("LeftHand", IE_Released, this, &APlayerCharacter::LeftButtonReleased);

	// Set up attack and block mode
	InputComponent->BindAction("AttackMode", IE_Pressed, this, &APlayerCharacter::AttackModeEnter);
	InputComponent->BindAction("AttackMode", IE_Released, this, &APlayerCharacter::AttackModeEnd);
	InputComponent->BindAction("BlockMode", IE_Pressed, this, &APlayerCharacter::BlockModeEnter);
	InputComponent->BindAction("BlockMode", IE_Released, this, &APlayerCharacter::BlockModeEnd);

}

/*-------------------------------------------------
------------    Function declaration    -----------
-------------------------------------------------*/



// Convert the screen coordinates to a centered system
FVector2D APlayerCharacter::CenterCoordinates(float LocationX, float LocationY)
{
	FVector2D Position = FVector2D(LocationX, LocationY);

	// Position minus half of the screen size to shift it to the center
	Position = Position - (0.5f * (GEngine->GameViewport->Viewport->GetSizeXY()));

	// Invert Y-value since it originally starts on the upper left corner
	Position.Y = Position.Y * -1.0f;
	return Position;
}

// Calculate the angle of a 2D-vector in degrees
float APlayerCharacter::Vector2DAngle(FVector2D Vector)
{
	float Angle;
	if (Vector.Y > 0.0f)
	{
		Angle = FMath::RadiansToDegrees(FMath::Acos(Vector.X / Vector.Size()));
	}
	else
	{
		// 360 minus the angle to get it for the lower part of the coordinate system
		Angle = 360.0f - FMath::RadiansToDegrees(FMath::Acos(Vector.X / Vector.Size()));
	}
	return Angle;
}


// Calculate the position of the mouse with a centered coordinate system
void APlayerCharacter::CalculateMouse()
{
	APlayerController* PlayerController = Cast<APlayerController>(GetController());
	if (PlayerController != nullptr)
	{
		// Get the mouseposition and safe it
		float LocationX;
		float LocationY;
		PlayerController->GetMousePosition(LocationX, LocationY);

		// Center the position and safe it
		MousePosition = CenterCoordinates(LocationX, LocationY);

	}
}

// Generate an artificial mouse with a limited speed that is following the actual mouse
void APlayerCharacter::CalculateArtificialMouse()
{
	// Check if artificial mouse is approximatly at the target position
	if (!(FMath::IsNearlyEqual(ArtificialMouse.X, MousePosition.X, 0.05f) && FMath::IsNearlyEqual(ArtificialMouse.Y, MousePosition.Y, 0.05f)))
	{
		// Make a vector pointing to the actual mouse position with a lenght of 0.0125 multiplied with the attspeed
		FVector2D PointingVector;
		PointingVector = FVector2D(MousePosition.X - ArtificialMouse.X, MousePosition.Y - ArtificialMouse.Y);
		PointingVector *= (1.0f / PointingVector.Size() * 0.0125f);

		// Add the vector to the artificial mouse position
		ArtificialMouse += PointingVector;
		// Calculate the angle and the length of the vector
		ArtificialMouseAngle = Vector2DAngle(ArtificialMouse);
		ArificialVectorLength = ArtificialMouse.Size();

	}
}

// Handles attack and block mode input
void APlayerCharacter::AttackModeEnter()
{
	bAttackMode = true;
}

void APlayerCharacter::AttackModeEnd()
{
	bAttackMode = false;
	ActionEnum = EActionEnum::AE_Nothing;
}

void APlayerCharacter::BlockModeEnter()
{
	bBlockMode = true;
}

void APlayerCharacter::BlockModeEnd()
{
	bBlockMode = false;
	ActionEnum = EActionEnum::AE_Nothing;
}

// Handles mouse input and passes it on to the next functions
void APlayerCharacter::RightButtonPressed()
{
	OnMouseClick(true);
}

void APlayerCharacter::RightButtonReleased()
{
	OnMouseRelease(true);
}

void APlayerCharacter::LeftButtonPressed()
{
	OnMouseClick(false);
}

void APlayerCharacter::LeftButtonReleased()
{
	OnMouseRelease(false);
}

// Decides what to do when a mouse button is clicked
void APlayerCharacter::OnMouseClick(bool bRight)
{
	if (bAttackMode)
	{
		CalculateMouse();
	}
	else if (bBlockMode)
	{
		ActionEnum = EActionEnum::AE_Blocking;
	}

}

// Decides what to do when a mouse button is released
void APlayerCharacter::OnMouseRelease(bool bRight)
{
	if (bAttackMode)
	{
		// Get the angle of the vector between the mousepositon on click and after release
		FVector2D LocalMousePosition = MousePosition;
		CalculateMouse();
		LocalMousePosition -= MousePosition;
		DrawAngle = Vector2DAngle(LocalMousePosition);
		ActionEnum = EActionEnum::AE_Attacking;
	}

}