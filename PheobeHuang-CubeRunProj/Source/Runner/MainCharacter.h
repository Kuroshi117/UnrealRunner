// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "MainCharacter.generated.h"

class USpringArmComponent;
class UCameraComponent;
class UStaticMeshComponent;
class ARotatingStage;
class UCapsuleComponent;
class AObstacleSpawn;
class UBoxComponent;
class ADestroyVolume;

UCLASS()
class RUNNER_API AMainCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AMainCharacter();

	UPROPERTY(EditAnywhere, BlueprintReadonly, Category="Camera")
		class USpringArmComponent* SpringArm;

	UPROPERTY(EditAnywhere, BlueprintReadonly, Category = "Camera")
		class UCameraComponent* Camera;

	UPROPERTY(VisibleAnywhere, BlueprintReadonly, Category = "Player")
		UStaticMeshComponent* CubeMesh;

	//UPROPERTY(VisibleAnywhere, BlueprintReadonly, Category = "Player")
		//UCapsuleComponent* Capsule;

	UPROPERTY(VisibleAnywhere, BlueprintReadonly, Category = "Player")
		UBoxComponent* BoxCollider;

	class ARotatingStage* RotatingStage;

	class ADestroyVolume* DestroyVol;

	bool IsAlive;


protected:
	// Called when the game starts or when spawned
	UFUNCTION(BluePrintCallable)
	virtual void BeginPlay() override;

	float MoveSpeed;

	float ClampRange;


public:	
	// Called every frame
	UFUNCTION(BluePrintCallable)
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	UFUNCTION(BluePrintCallable)
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	//FVector CurVelocty;
	UFUNCTION(BluePrintCallable)
		void MoveRight(float Value);

	UFUNCTION(BluePrintCallable)
		void RotateRight(float Value);

	UFUNCTION(BluePrintCallable)
		void OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

};
