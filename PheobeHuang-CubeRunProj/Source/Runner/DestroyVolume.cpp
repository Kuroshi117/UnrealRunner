// Fill out your copyright notice in the Description page of Project Settings.


#include "DestroyVolume.h"
#include "Components/BoxComponent.h"

// Sets default values
ADestroyVolume::ADestroyVolume()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	CollideBox = CreateDefaultSubobject<UBoxComponent>(TEXT("CollideBox"));
	SetRootComponent(CollideBox);
	CollideBox->SetEnableGravity(false);
}

// Called when the game starts or when spawned
void ADestroyVolume::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ADestroyVolume::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

