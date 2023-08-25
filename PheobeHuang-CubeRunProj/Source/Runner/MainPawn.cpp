// Fill out your copyright notice in the Description page of Project Settings.
#include "MainPawn.h"
#include "GameFramework/Pawn.h"
#include "Components/InputComponent.h"
#include "Camera/CameraComponent.h"
#include "Classes/GameFramework/FloatingPawnMovement.h" 
#include "Classes/Components/StaticMeshComponent.h"

// Sets default values
AMainPawn::AMainPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	CreateDefaultSubobject<UFloatingPawnMovement>("PawnMovement");

	CubeMesh = CreateDefaultSubobject<UStaticMeshComponent>("CubeMesh");
	Camera = CreateDefaultSubobject<UCameraComponent>("Camera");

	Camera->SetupAttachment(CubeMesh);

	SetRootComponent(CubeMesh);
}

// Called when the game starts or when spawned
void AMainPawn::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AMainPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AMainPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveHoriztonal", this, &AMainPawn::MoveHorizontal);

}

void AMainPawn::MoveHorizontal(float value) 
{
	//AddMovementInput(GetActorRightVector(), value);

	//FloatingPawnMovement->AddInputVector(GetActorRightVector() * value);
}

