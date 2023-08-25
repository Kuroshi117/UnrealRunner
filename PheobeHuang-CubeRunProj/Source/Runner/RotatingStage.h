// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "RotatingStage.generated.h"


UCLASS()
class RUNNER_API ARotatingStage : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ARotatingStage();

	UPROPERTY(VisibleAnywhere, BlueprintReadonly)
		UStaticMeshComponent* RootEmpty;

	UPROPERTY(VisibleAnywhere, BlueprintReadonly, Category = "Wall")
		UStaticMeshComponent* FirstWall;

	UPROPERTY(VisibleAnywhere, BlueprintReadonly, Category = "Wall")
		UStaticMeshComponent* SecondWall;

	UPROPERTY(VisibleAnywhere, BlueprintReadonly, Category = "Wall")
		UStaticMeshComponent* ThirdWall;

	UPROPERTY(VisibleAnywhere, BlueprintReadonly, Category = "Wall")
		UStaticMeshComponent* FourthWall;

	void RotateRight(float Value);

	//void MoveRight(float Value);

	float RollValue;

	float InputValue;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;


public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
