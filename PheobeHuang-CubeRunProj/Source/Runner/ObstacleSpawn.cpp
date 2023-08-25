// Fill out your copyright notice in the Description page of Project Settings.


#include "ObstacleSpawn.h"
#include "ObstacleWall.h"
#include "Engine/World.h"
#include "TimerManager.h"
#include "RotatingStage.h"
#include "EngineUtils.h"

// Sets default values
AObstacleSpawn::AObstacleSpawn()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	Root->SetVisibility(false);
	RootComponent = Root;

	SpawnInterval = 1.5f;

	RotStage = nullptr;

}

// Called when the game starts or when spawned
void AObstacleSpawn::BeginPlay()
{
	//SpawnWall();
	SetSpawnActive(true);

	for (TActorIterator<ARotatingStage> StageItr(GetWorld()); StageItr; ++StageItr) {
		RotStage = Cast<ARotatingStage>(*StageItr);
	}
	RollV = RotStage->RollValue;

	Super::BeginPlay();
}

// Called every frame
void AObstacleSpawn::Tick(float DeltaTime)
{
	InputV = RotStage->InputValue;
	FRotator NewRotation = FRotator(GetActorRotation().Pitch, GetActorRotation().Yaw, GetActorRotation().Roll + InputV * RollV);
	FQuat QuatRotation = FQuat(NewRotation);
	SetActorRotation(QuatRotation);

	Super::Tick(DeltaTime);

}

void AObstacleSpawn::SpawnWall()//change later to reduce memory issues
{
	if (WallArray[0]!=NULL) {
		FActorSpawnParameters SpawnParams;
		//SpawnParams.Owner = this;
		//SpawnParams.Instigator = Instigator;

		int ObsNum = rand() % WallArray.Num();

		int OffSet = rand() % 4;
		OffSet *= 90;
		FRotator StartRot = FRotator(GetActorRotation().Pitch, GetActorRotation().Yaw, GetActorRotation().Roll+OffSet);
		FVector StartLoc = GetActorLocation();
		GetWorld()->SpawnActor<AObstacleWall>(WallArray[ObsNum], StartLoc, StartRot, SpawnParams);
	}
}

void AObstacleSpawn::SetSpawnActive(bool IsActive)
{ 
	if(IsActive)
	{
		GetWorldTimerManager().SetTimer(THandle, this, &AObstacleSpawn::SpawnWall, SpawnInterval, true, 1.0f);
	}
	else {
		GetWorldTimerManager().ClearTimer(THandle);
	}
}



