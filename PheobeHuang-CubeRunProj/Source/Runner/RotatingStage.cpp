// Fill out your copyright notice in the Description page of Project Settings.


#include "RotatingStage.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/PawnMovementComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/Controller.h"



// Sets default values
ARotatingStage::ARotatingStage()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	RootEmpty = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("RootEmpty"));
	FirstWall = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("FirstWall"));
	SecondWall = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("SecondWall"));
	ThirdWall= CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ThirdWall"));
	FourthWall = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("FourthWall"));

	RootEmpty->SetupAttachment(RootComponent);
	FirstWall->SetupAttachment(RootEmpty);
	SecondWall->SetupAttachment(RootEmpty);
	ThirdWall->SetupAttachment(RootEmpty);
	FourthWall->SetupAttachment(RootEmpty);

	RootEmpty->SetEnableGravity(false);
	FirstWall->SetEnableGravity(false);
	SecondWall->SetEnableGravity(false);
	ThirdWall->SetEnableGravity(false);
	FourthWall->SetEnableGravity(false);

	RollValue = 1.f;

	InputValue = 0.f;
}


// Called when the game starts or when spawned
void ARotatingStage::BeginPlay()
{
	Super::BeginPlay();
	

}

// Called every frame
void ARotatingStage::Tick(float DeltaTime)
{
	

	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ARotatingStage::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	//PlayerInputComponent->BindAxis("RotateRight", this, &ARotatingStage::RotateRight);

}

void ARotatingStage::RotateRight(float Value) {
	InputValue = Value;
	FRotator NewRotation = FRotator(GetActorRotation().Pitch, GetActorRotation().Yaw, GetActorRotation().Roll+Value*RollValue);
	FQuat QuatRotation = FQuat(NewRotation);
	SetActorRotation(QuatRotation);
}


/*void ARotatingStage::MoveRight(float Value)
{
	if (Value != 0.0f) {
		FVector Direction = FVector(GetActorLocation().X, GetActorLocation().Y + Value * 10.f, GetActorLocation().Z);
		SetActorLocation(Direction);
	}
}*/
