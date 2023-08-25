// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DestroyVolume.generated.h"


class UBoxComponent;

UCLASS()
class RUNNER_API ADestroyVolume : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ADestroyVolume();

	UPROPERTY(VisibleAnywhere, BlueprintReadonly)
		UBoxComponent* CollideBox;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
