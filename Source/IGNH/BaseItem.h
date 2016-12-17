// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "Util.h"
#include "BaseItem.generated.h"


UCLASS()
class IGNH_API ABaseItem : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABaseItem();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	// Basic attributes
	UPROPERTY(VisibleDefaultsOnly, Category = General)
		FString Name;
	UPROPERTY(VisibleDefaultsOnly, Category = General)
		UTexture2D* ItemImage;
	UPROPERTY(VisibleDefaultsOnly, Category = General)
		USkeletalMesh* SkeletalMesh;
	UPROPERTY(VisibleDefaultsOnly, Category = General)
		UStaticMesh* Mesh;
	UPROPERTY(VisibleDefaultsOnly, Category = General)
		float Weight;
	UPROPERTY(VisibleDefaultsOnly, Category = General)
		FVector2D SizeInInventory;
	UPROPERTY(VisibleDefaultsOnly, Category = General)
		EItemEnum ItemEnum;
	UPROPERTY(VisibleDefaultsOnly, Category = General)
		int Level;
	UPROPERTY(VisibleDefaultsOnly, Category = General)
		int MaxStacksize;
	UPROPERTY()
		int CurrentStacksize;

	// Basic functions
	UFUNCTION()
		void PickUp();
	
	
};
