// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ObstacleSpawn.generated.h"

class AObstacleWall;
class ARotatingStage;

UCLASS()
class RUNNER_API AObstacleSpawn : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AObstacleSpawn();

	UPROPERTY(EditAnywhere, BlueprintReadonly)
		USceneComponent* Root;

	//UPROPERTY(EditAnywhere, Category = "Spawn")
		//TSubclassOf<class AObstacleWall> SWall;

	UPROPERTY(EditAnywhere, Category = "Spawn")
		TArray<TSubclassOf<class AObstacleWall>> WallArray;

	//class AObstacleWall* SpawnedWall;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	class ARotatingStage* RotStage;

	float InputV;

	float RollV;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable)
		void SpawnWall();

	float SpawnInterval;

	FTimerHandle THandle;

	UFUNCTION(BlueprintCallable)
		void SetSpawnActive(bool IsActive);

};
