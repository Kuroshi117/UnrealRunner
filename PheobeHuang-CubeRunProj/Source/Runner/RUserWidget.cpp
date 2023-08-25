// Fill out your copyright notice in the Description page of Project Settings.


#include "RUserWidget.h"
#include "Components/TextBlock.h"
#include "RunnerGameModeBase.h"
#include "Components/PanelWidget.h"
#include "Components//Button.h"
#include "Kismet/GameplayStatics.h"

void URUserWidget::NativeConstruct()
{
	Super::NativeConstruct();

	RunGameMode = Cast<ARunnerGameModeBase>(GetWorld()->GetAuthGameMode());

	/*ScoreText = RunGameMode->GetScore();*/
	//ScorePanel->AddChild(ScoreBlock);
	ScoreBlock->SetText(ScoreText);


	//StartPanel->AddChild(StartButton);
	//StartPanel->AddChild(InstructButton);
	//StartPanel->AddChild(QuitButton);
	//StartPanel->AddChild(TitleText);
	//StartPanel->SetVisibility(ESlateVisibility::Collapsed);
	TitleText->SetText(FText::FromString("Cube Run\nby Phoebe Huang"));
	StartButtonText->SetText(FText::FromString("Start"));
	InstructButtonText->SetText(FText::FromString("Instructions"));
	QuitButtonText->SetText(FText::FromString("Quit"));
	GameOverText->SetText(FText::FromString("Game Over"));
	HighScoreList = FText::FromString("");
	ToMainText->SetText(FText::FromString("Main Menu"));
	ClearText->SetText(FText::FromString("Clear Scores"));
	OverQuitText->SetText(FText::FromString("Quit"));
	InstructTitleText->SetText(FText::FromString("Instructions"));
	InstructionsText->SetText(FText::FromString("Avoid the obstacles\nLeft Right-Move cube horizontally\nA D-Rotate world"));
	BackButtonText->SetText(FText::FromString("Back"));
	
	//optimize later
	if (!StartButton->OnClicked.IsBound())
	{
		StartButton->OnClicked.AddDynamic(this, &URUserWidget::OnStartClick);
	}

	if (!InstructButton->OnClicked.IsBound())
	{
		InstructButton->OnClicked.AddDynamic(this, &URUserWidget::OnInstructClick);
	}

	if (!QuitButton->OnClicked.IsBound())
	{
		QuitButton->OnClicked.AddDynamic(this, &URUserWidget::OnQuitClick);
	}

	if (!ToMainButton->OnClicked.IsBound())
	{
		ToMainButton->OnClicked.AddDynamic(this, &URUserWidget::ToMainClick);
	}

	if (!ClearButton->OnClicked.IsBound())
	{
		ClearButton->OnClicked.AddDynamic(this, &URUserWidget::ClearClick);
	}

	if (!OverQuitButton->OnClicked.IsBound())
	{
		OverQuitButton->OnClicked.AddDynamic(this, &URUserWidget::OverQuitClick);
	}

	if (!BackButton->OnClicked.IsBound())
	{
		BackButton->OnClicked.AddDynamic(this, &URUserWidget::OnBackClick);
	}
}

void URUserWidget::SynchronizeProperties()
{
	Super::SynchronizeProperties();

	ScoreBlock->SetText(ScoreText);

	
}

void URUserWidget::OnStartClick()
{
	RunGameMode->SetCurrentState(ERunnerState::EPlaying);
}

void URUserWidget::OnInstructClick()
{
	RunGameMode->SetCurrentState(ERunnerState::EInstructions);
}

void URUserWidget::OnQuitClick()
{
	FGenericPlatformMisc::RequestExit(false);//May change so editor won't quit, too
}

void URUserWidget::ToMainClick()
{
	UGameplayStatics::OpenLevel(this, (*GetWorld()->GetName()), false);
	RunGameMode->SetCurrentState(ERunnerState::EStartMenu);
}

void URUserWidget::ClearClick()
{
	UGameplayStatics::OpenLevel(this, (*GetWorld()->GetName()), false);
	RunGameMode->ClearScoreBoard();
	RunGameMode->SetCurrentState(ERunnerState::EStartMenu);
}

void URUserWidget::OverQuitClick()
{
	FGenericPlatformMisc::RequestExit(false);//May change so editor won't quit, too
}

void URUserWidget::OnBackClick()
{
	RunGameMode->SetCurrentState(ERunnerState::EStartMenu);
}

void URUserWidget::UpdateFinalScore(){ 
	HighTitleText->SetText(FText::FromString("Score: " + ScoreText.ToString()+"\nHigh Scores"));
	//HighScoreList = FText::FromString("Temp");//Temp Text for list of High Scores
	HighScoreText->SetText(HighScoreList); 
}