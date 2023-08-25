// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "RunnerGameModeBase.generated.h"

UENUM(BlueprintType)
enum class ERunnerState:uint8 
{
	EStartMenu, 
	EInstructions, 
	EPlaying, 
	EGameOver, 
	EUnknown
};

class AMainCharacter;
class AObstacleSpawn;

/**
 * 
 */
UCLASS()
class RUNNER_API ARunnerGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

public:

	ARunnerGameModeBase();

	UFUNCTION(BlueprintPure, Category="Score")
		int GetScore() const;

	UFUNCTION(BlueprintCallable, Category = "Score")
		void AddScore(int ScoreToAdd);

	UFUNCTION(BlueprintPure, Category="State")
		ERunnerState GetCurrentState() const;

	UFUNCTION(BlueprintCallable, Category = "State")
		void SetCurrentState(ERunnerState NewState);

	virtual void Tick(float DeltaTime) override;

	virtual void BeginPlay() override;

	UFUNCTION()
		void ClearScoreBoard();

protected:
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Score", Meta=(BlueprintProtected="true"))
		int Score;

	UPROPERTY(EditDefaultsOnly, BluePrintReadonly, Category = "Player UI", Meta = (BlueprintProtected = "true"))
		TSubclassOf<class URUserWidget> RunnerWidget;

	UPROPERTY()
		class URUserWidget* CurWidget;

	//UPROPERTY()
	class AMainCharacter* Main;

	//UPROPERTY()
	class AObstacleSpawn* ObSpawn;

	UPROPERTY(EditAnywhere)
		TArray<int> ScoreBoard;

private:

	ERunnerState CurrentState;

	void HandleNewState(ERunnerState NewState);

	UPROPERTY()
	class URunnerSaveGame* RunSave;

	void SetScoreBoard();

};
