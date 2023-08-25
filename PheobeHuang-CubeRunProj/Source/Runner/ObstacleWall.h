// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ObstacleWall.generated.h"

class ARotatingStage;
class UBoxComponent;
class ADestroyVolume;
class AMainCharacter;
class ARunnerGameModeBase;

UCLASS()
class RUNNER_API AObstacleWall : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AObstacleWall();

	float RushSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadonly)
		USceneComponent* RootEmpty;

	UPROPERTY(VisibleAnywhere, BlueprintReadonly, Category = "Wall")
		UStaticMeshComponent* FirstWall;

	UPROPERTY(VisibleAnywhere, BlueprintReadonly, Category = "Wall")
		UStaticMeshComponent* SecondWall;

	UPROPERTY(VisibleAnywhere, BlueprintReadonly, Category = "Wall")
		UStaticMeshComponent* ThirdWall;

	UPROPERTY(VisibleAnywhere, BlueprintReadonly)
		UBoxComponent* FirstBox;

	UPROPERTY(VisibleAnywhere, BlueprintReadonly)
		UBoxComponent* SecondBox;

	UPROPERTY(VisibleAnywhere, BlueprintReadonly)
		UBoxComponent* ThirdBox;

	float RollVal;

	float InputVal;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	class ARotatingStage* RotStage;

	class ADestroyVolume* DesVol;

	class ARunnerGameModeBase* RunGameMode;

	//class AMainCharacter* Main;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
		void OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

};
