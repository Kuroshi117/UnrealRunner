// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "RUserWidget.generated.h"
/**
 * 
 */

class UTextBlock;
class ARunnerGameModeBase;

UCLASS()
class RUNNER_API URUserWidget : public UUserWidget
{
	GENERATED_BODY()

public:

	virtual void NativeConstruct() override;

	virtual void SynchronizeProperties() override;



	UPROPERTY(EditAnywhere, meta = (BindWidget))
		class UPanelWidget* ScorePanel;

	UPROPERTY(EditAnywhere, meta=(BindWidget))
		class UTextBlock* ScoreBlock;

	UPROPERTY(EditAnywhere)
		FText ScoreText;

	
	UPROPERTY(EditAnywhere, meta = (BindWidget))
		class UPanelWidget* StartPanel;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
		class UButton* StartButton;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
		class UButton* InstructButton;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
		class UButton* QuitButton;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
		class UTextBlock* TitleText;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
		class UTextBlock* StartButtonText;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
		class UTextBlock* InstructButtonText;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
		class UTextBlock* QuitButtonText;

	UFUNCTION()
		void OnStartClick();

	UFUNCTION()
		void OnInstructClick();

	UFUNCTION()
		void OnQuitClick();


	UPROPERTY(EditAnywhere, meta = (BindWidget))
		class UPanelWidget* GameOverPanel;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
		class UTextBlock* GameOverText;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
		class UTextBlock* HighScoreText;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
		class UTextBlock* HighTitleText;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
		class UTextBlock* ToMainText;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
		class UTextBlock* ClearText;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
		class UTextBlock* OverQuitText;

	UPROPERTY(EditAnywhere)
		FText HighScoreList;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
		class UButton* ToMainButton;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
		class UButton* ClearButton;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
		class UButton* OverQuitButton;

	UFUNCTION()
		void UpdateFinalScore();

	UFUNCTION()
		void ToMainClick();

	UFUNCTION()
		void ClearClick();

	UFUNCTION()
		void OverQuitClick();


	UPROPERTY(EditAnywhere, meta = (BindWidget))
		class UPanelWidget* InstructPanel;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
		class UTextBlock* InstructTitleText;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
		class UTextBlock* InstructionsText;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
		class UTextBlock* BackButtonText;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
		class UButton* BackButton;

	UFUNCTION()
		void OnBackClick();

private:

	class ARunnerGameModeBase* RunGameMode;

	


	
};
