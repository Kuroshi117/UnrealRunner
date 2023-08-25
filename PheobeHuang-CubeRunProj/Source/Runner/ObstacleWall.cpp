// Fill out your copyright notice in the Description page of Project Settings.


#include "ObstacleWall.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "EngineUtils.h"
#include "RotatingStage.h"
#include "DestroyVolume.h"
#include "MainCharacter.h"
#include "RunnerGameModeBase.h"

#include "Engine.h"

// Sets default values
AObstacleWall::AObstacleWall()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	RootEmpty = CreateDefaultSubobject<USceneComponent>(TEXT("RootEmpty"));
	FirstWall = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("FirstWall"));
	SecondWall = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("SecondWall"));
	ThirdWall = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ThirdWall"));

	//RootEmpty->SetupAttachment(RootComponent);
	RootComponent = RootEmpty;
	FirstWall->SetupAttachment(RootEmpty);
	SecondWall->SetupAttachment(RootEmpty);
	ThirdWall->SetupAttachment(RootEmpty);

	RootEmpty->SetVisibility(true);
	FirstWall->SetVisibility(true);
	SecondWall->SetVisibility(true);
	ThirdWall->SetVisibility(true);

	//RootEmpty->SetEnableGravity(false);
	FirstWall->SetEnableGravity(false);
	SecondWall->SetEnableGravity(false);
	ThirdWall->SetEnableGravity(false);

	FirstBox = CreateDefaultSubobject<UBoxComponent>(TEXT("FirstBox"));
	FirstBox->SetGenerateOverlapEvents(true);
	FirstBox->SetupAttachment(FirstWall);

	SecondBox = CreateDefaultSubobject<UBoxComponent>(TEXT("SecondBox"));
	SecondBox->SetGenerateOverlapEvents(true);
	SecondBox->SetupAttachment(SecondWall);

	ThirdBox = CreateDefaultSubobject<UBoxComponent>(TEXT("ThirdBox"));
	ThirdBox->SetGenerateOverlapEvents(true);
	ThirdBox->SetupAttachment(ThirdWall);

	RushSpeed = 35.f;

	RotStage = nullptr;
	DesVol = nullptr;

}

// Called when the game starts or when spawned
void AObstacleWall::BeginPlay()
{
	FirstBox->OnComponentBeginOverlap.AddDynamic(this, &AObstacleWall::OnOverlapBegin);
	SecondBox->OnComponentBeginOverlap.AddDynamic(this, &AObstacleWall::OnOverlapBegin);
	ThirdBox->OnComponentBeginOverlap.AddDynamic(this, &AObstacleWall::OnOverlapBegin);

	RunGameMode = Cast<ARunnerGameModeBase>(GetWorld()->GetAuthGameMode());

	for (TActorIterator<ARotatingStage> StageItr(GetWorld()); StageItr; ++StageItr) {
		RotStage = Cast<ARotatingStage>(*StageItr);
	}
	RollVal = RotStage->RollValue;

	for (TActorIterator<ADestroyVolume> StageItr(GetWorld()); StageItr; ++StageItr) {
		DesVol = Cast<ADestroyVolume>(*StageItr);
	}


	Super::BeginPlay();
	
}

// Called every frame
void AObstacleWall::Tick(float DeltaTime)
{
	FVector Direction = FVector(GetActorLocation().X - RushSpeed, GetActorLocation().Y, GetActorLocation().Z);
	SetActorLocation(Direction);

	InputVal = RotStage->InputValue;
	FRotator NewRotation = FRotator(GetActorRotation().Pitch, GetActorRotation().Yaw, GetActorRotation().Roll + InputVal * RollVal);
	FQuat QuatRotation = FQuat(NewRotation);
	SetActorRotation(QuatRotation);

	Super::Tick(DeltaTime);

}

void AObstacleWall::OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) 
{
	if (OtherActor && (OtherActor != this) && OtherComp )
	{
		
		/*for (TActorIterator<AMainCharacter> StageItr(GetWorld()); StageItr; ++StageItr) {
			Main = Cast<AMainCharacter>(*StageItr);
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Match"));
		}*/
		if(OtherActor==DesVol)
		{
			//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Hit"));
			//RunWidge->UpdateScore();
			RunGameMode->AddScore(1);
			Destroy();
		}
		/*else if(OtherActor==Main)
		{
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Main"));
			//OtherActor->Destroy();
			//RushSpeed *= -1.f;

			OtherActor->SetActorEnableCollision(false);
			OtherActor->SetActorHiddenInGame(true);

			DesVol->SetActorEnableCollision(false);
		}
		else
		{
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Other"));
		}*/
	}
}