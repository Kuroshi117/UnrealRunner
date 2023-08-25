// Fill out your copyright notice in the Description page of Project Settings.


#include "MainCharacter.h"
#include "Components/InputComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/Controller.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "RotatingStage.h"
#include "EngineUtils.h"
#include "Components/BoxComponent.h"
#include "DestroyVolume.h"

// Sets default values
AMainCharacter::AMainCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	//Set to false unless Tick needed
	PrimaryActorTick.bCanEverTick = true;

	CubeMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("CubeMesh"));
	CubeMesh->SetupAttachment(RootComponent);

	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	//SpringArm->SetupAttachment(RootComponent);
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(SpringArm);

	CubeMesh->SetEnableGravity(false);
	
	//Capsule = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Capsule"));
	//Capsule->SetEnableGravity(false);
	//Capsule->SetGenerateOverlapEvents(true);
	//Capsule->SetupAttachment(CubeMesh);

	BoxCollider = CreateDefaultSubobject<UBoxComponent>(TEXT("Box Collider"));
	BoxCollider->SetEnableGravity(false);
	BoxCollider->SetGenerateOverlapEvents(true);
	BoxCollider->SetupAttachment(RootComponent);


	MoveSpeed = 10.f;
	ClampRange = 550.f;
	
	RotatingStage = nullptr; //Cast<ARotatingStage>();
	DestroyVol = nullptr;

	IsAlive = true;
}

// Called when the game starts or when spawned
void AMainCharacter::BeginPlay()
{
	for (TActorIterator<ARotatingStage> StageItr(GetWorld()); StageItr; ++StageItr) {
		RotatingStage = Cast<ARotatingStage>(*StageItr);
	}
	for (TActorIterator<ADestroyVolume> StageItr(GetWorld()); StageItr; ++StageItr) {
		DestroyVol = Cast<ADestroyVolume>(*StageItr);
	}

	BoxCollider->OnComponentBeginOverlap.AddDynamic(this, &AMainCharacter::OnOverlapBegin);
	Super::BeginPlay();

}

// Called every frame
void AMainCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	/*if (!CurVelocty.IsZero())
	{
		FVector NewLocation = GetActorLocation() + (CurVelocty*DeltaTime);
		SetActorLocation(NewLocation);
	}*/

}

// Called to bind functionality to input
void AMainCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	
	PlayerInputComponent->BindAxis("MoveRight", this, &AMainCharacter::MoveRight);
	PlayerInputComponent->BindAxis("RotateRight", this, &AMainCharacter::RotateRight);

}

void AMainCharacter::MoveRight(float Value)
{
	
	if ((Controller != NULL) && (Value != 0.0f))
	{
		/*const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
  		AddMovementInput(Direction, Value);*/
		//AddMovementInput(GetActorRightVector(), Value);
		FVector Direction=FVector(GetActorLocation().X, GetActorLocation().Y+Value*MoveSpeed, GetActorLocation().Z);
		if (Direction.Y > ClampRange||Direction.Y < -ClampRange)
		{
			Direction=FVector(GetActorLocation().X, GetActorLocation().Y, GetActorLocation().Z);
		}

		SetActorLocation(Direction);

	}

	//CurVelocty.X = FMath::Clamp(Value, -1.0f, 1.0f)*100.0f;
}

void AMainCharacter::RotateRight(float Value)
{
	if (RotatingStage)
	{
		RotatingStage->RotateRight(Value);
	}
}

void AMainCharacter::OnOverlapBegin(UPrimitiveComponent * OverlappedComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	if (OtherActor && (OtherActor != this) && OtherComp && (OtherActor !=RotatingStage))
	{
		this->SetActorEnableCollision(false);
		this->SetActorHiddenInGame(true);
		IsAlive = false;
		DestroyVol->SetActorEnableCollision(false);
	}
}
