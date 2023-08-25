// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.


#include "RunnerGameModeBase.h"
#include "Blueprint/UserWidget.h"
#include "RUserWidget.h"
#include "Kismet/GameplayStatics.h"
#include "Maincharacter.h"
#include "Components/TextBlock.h"
#include "ObstacleSpawn.h"
#include "EngineUtils.h"
#include "Components/PanelWidget.h"
#include "GameFramework/Pawn.h"
#include "RunnerSaveGame.h"

ARunnerGameModeBase::ARunnerGameModeBase()
{
	PrimaryActorTick.bCanEverTick = true;	
}

void ARunnerGameModeBase::BeginPlay()
{
	Super::BeginPlay();

	RunSave = Cast<URunnerSaveGame>(UGameplayStatics::CreateSaveGameObject(URunnerSaveGame::StaticClass()));
	if (UGameplayStatics::DoesSaveGameExist("SlotOne", 0)) {
		RunSave = Cast<URunnerSaveGame>(UGameplayStatics::LoadGameFromSlot("SlotOne", 0));
		ScoreBoard = RunSave->HighScoreBoard;
		//ScoreBoard.Init(0, 5);
	}
	else {
		ScoreBoard.Init(0, 5);
	}

	for (TActorIterator<AObstacleSpawn> StageItr(GetWorld()); StageItr; ++StageItr) {
		ObSpawn = Cast<AObstacleSpawn>(*StageItr);
	}

	if (!Main)
	{
		Main = Cast<AMainCharacter>(UGameplayStatics::GetPlayerPawn(this, 0));
		Score = 0;
	}
	else { 
		Score = 0; 
	}

	if (CurWidget != nullptr)
	{
		CurWidget->RemoveFromViewport();
		CurWidget = nullptr;
	}

	if (RunnerWidget != nullptr)
	{
		CurWidget = CreateWidget<URUserWidget>(GetWorld(), RunnerWidget);
		if (CurWidget != nullptr)
		{
			CurWidget->ScoreText = FText::FromString(FString::FromInt(Score));
			CurWidget->AddToViewport();

			
		}
	}

	APlayerController* PController = GetWorld()->GetFirstPlayerController();
	if (PController) {
		PController->bShowMouseCursor = true;
		PController->bEnableClickEvents = true;
		PController->bEnableMouseOverEvents = true;
	}

	SetCurrentState(ERunnerState::EStartMenu);
}

void ARunnerGameModeBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (Main) {
		if (Main->IsAlive == false && GetCurrentState() != ERunnerState::EGameOver)
		{
			SetCurrentState(ERunnerState::EGameOver);
			
		}
	}
	//to increase difficulty
	//need to modify base speed first and increase spawn interval time
	/*
	if (ObSpawn)
	{
		if (Score % 10 == 0 && Score > 0 && ObSpawn->SpawnInterval > 1)
		{
			ObSpawn->SpawnInterval -= 1;
		}
	}*/
}


int ARunnerGameModeBase::GetScore() const
{
	return Score;
}

void ARunnerGameModeBase::AddScore(int ScoreToAdd)
{
	Score += ScoreToAdd;
	CurWidget->ScoreText = FText::FromString(FString::FromInt(Score));
	CurWidget->ScoreBlock->SetText(CurWidget->ScoreText);
}

ERunnerState ARunnerGameModeBase::GetCurrentState() const
{
	return CurrentState;
}

void ARunnerGameModeBase::SetCurrentState(ERunnerState NewState)
{
	CurrentState = NewState;
	HandleNewState(CurrentState);
}

void ARunnerGameModeBase::HandleNewState(ERunnerState NewState)
{
	//Not the most optimal, but works for now
	switch (NewState) {

	case ERunnerState::EStartMenu: {
		CurWidget->StartPanel->SetVisibility(ESlateVisibility::Visible);
		CurWidget->InstructPanel->SetVisibility(ESlateVisibility::Collapsed);
		CurWidget->ScorePanel->SetVisibility(ESlateVisibility::Collapsed);
		CurWidget->GameOverPanel->SetVisibility(ESlateVisibility::Collapsed);	
		Score = 0;
		ObSpawn->SetSpawnActive(false);
		Main->SetActorEnableCollision(false);
		break;
	}
	case ERunnerState::EInstructions: {
		CurWidget->InstructPanel->SetVisibility(ESlateVisibility::Visible);
		CurWidget->StartPanel->SetVisibility(ESlateVisibility::Collapsed);
		CurWidget->ScorePanel->SetVisibility(ESlateVisibility::Collapsed);
		CurWidget->GameOverPanel->SetVisibility(ESlateVisibility::Collapsed);
		break;
	}
	case ERunnerState::EPlaying: {
		CurWidget->ScorePanel->SetVisibility(ESlateVisibility::Visible);
		CurWidget->StartPanel->SetVisibility(ESlateVisibility::Collapsed);
		CurWidget->InstructPanel->SetVisibility(ESlateVisibility::Collapsed);
		CurWidget->GameOverPanel->SetVisibility(ESlateVisibility::Collapsed);
		ObSpawn->SetSpawnActive(true);
		Main->SetActorEnableCollision(true);
		break;
	}
	case ERunnerState::EGameOver: {
		CurWidget->GameOverPanel->SetVisibility(ESlateVisibility::Visible);
		CurWidget->StartPanel->SetVisibility(ESlateVisibility::Collapsed);
		CurWidget->InstructPanel->SetVisibility(ESlateVisibility::Collapsed);
		CurWidget->ScorePanel->SetVisibility(ESlateVisibility::Collapsed);
		SetScoreBoard();
		ObSpawn->SetSpawnActive(false);
		CurWidget->UpdateFinalScore();
		break;
	}
	case ERunnerState::EUnknown:
	default: {

		break;
	}
	}

}

void ARunnerGameModeBase::SetScoreBoard()
{
	//RunSave->HighScoreBoard[0] = Score;
	//ScoreBoard.Emplace(Score);
	if (!RunSave) {
		RunSave = Cast<URunnerSaveGame>(UGameplayStatics::CreateSaveGameObject(URunnerSaveGame::StaticClass()));
	}

	for (int i = 0; i < ScoreBoard.Num(); i++) {
		if (Score > ScoreBoard[i]) {
			ScoreBoard.Insert(Score, i);
			//ScoreBoard.RemoveAt(5);
			
			//for (int j = (ScoreBoard.Num() - 1); j > i; j--)
			//{
			//	ScoreBoard[j + 1] = ScoreBoard[j];
			//}
			//RunSave->HighScoreBoard[i] = Score;
			break;
		}
		/*if (ScoreBoard[i] < ScoreBoard[i + 1])
		{
			int h = ScoreBoard[i];
			ScoreBoard[i] = ScoreBoard[i + 1];
			ScoreBoard[i + 1] = h;
		}*/
		//ScoreBoard[i] = 0;
	}
	ScoreBoard.SetNum(5);
	if (UGameplayStatics::DoesSaveGameExist("SlotOne",0))
	{
		RunSave->HighScoreBoard = ScoreBoard;
		UGameplayStatics::SaveGameToSlot(RunSave, TEXT("SlotOne"), 0);
	}
	else {
		RunSave = Cast<URunnerSaveGame>(UGameplayStatics::CreateSaveGameObject(URunnerSaveGame::StaticClass()));
		RunSave->HighScoreBoard = ScoreBoard;
		UGameplayStatics::SaveGameToSlot(RunSave, TEXT("SlotOne"), 0);
	}

	FString HSList;
	for (int i=0; i<ScoreBoard.Num();i++)
	{
		HSList.Append(FString::FromInt(i + 1) + "- " + FString::FromInt(ScoreBoard[i])+"\n");
	}
	CurWidget->HighScoreList = FText::FromString(HSList);
	CurWidget->HighScoreText->SetText(CurWidget->HighScoreList);
}

void ARunnerGameModeBase::ClearScoreBoard()
{
	for (int i=0; i < ScoreBoard.Num(); i++)
	{
		ScoreBoard[i]=0;
	}
	if (!RunSave) {
		RunSave = Cast<URunnerSaveGame>(UGameplayStatics::CreateSaveGameObject(URunnerSaveGame::StaticClass()));
	}
	if (UGameplayStatics::DoesSaveGameExist("SlotOne", 0))
	{
		RunSave->HighScoreBoard = ScoreBoard;
		UGameplayStatics::SaveGameToSlot(RunSave, TEXT("SlotOne"), 0);
	}
	else {
		RunSave = Cast<URunnerSaveGame>(UGameplayStatics::CreateSaveGameObject(URunnerSaveGame::StaticClass()));
		RunSave->HighScoreBoard = ScoreBoard;
		UGameplayStatics::SaveGameToSlot(RunSave, TEXT("SlotOne"), 0);
	}
}
