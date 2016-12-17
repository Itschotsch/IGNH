// Fill out your copyright notice in the Description page of Project Settings.

#include "IGNH.h"
#include "Useable.h"

// Sets default values
AUseable::AUseable()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AUseable::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void AUseable::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


