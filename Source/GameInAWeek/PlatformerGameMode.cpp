// Fill out your copyright notice in the Description page of Project Settings.


#include "PlatformerGameMode.h"
#include <Kismet/GameplayStatics.h>

void APlatformerGameMode::AddCoinToTotal()
{//increases the total coin count by one 
	totalCoins++;
} 

void APlatformerGameMode::coinFound()
{//increases the found count by one and decreases the total coin
	coinsFound++;
	totalCoins--;
}

int APlatformerGameMode::GetCoinTotal()
{//returns the total coins amount
	return totalCoins;
}

int APlatformerGameMode::GetCoinsFound()
{//returns the found coins amount 
	return coinsFound;
}

void APlatformerGameMode::setCheckpoint(FVector checkpointPos)
{//sets the players current checkpoint 
	CurrentCheckpoint = checkpointPos;
}

FVector APlatformerGameMode::GetCheckpoint()
{//returns the current checkpoint
	return CurrentCheckpoint;
}

void APlatformerGameMode::GameOver(bool Complete)
{
	InGame = false;//sets in game to false 
	winner = Complete;//sets the winner to true if the parameter is true 
	if (winner)GetWorld()->GetTimerManager().SetTimer(EndOfGameTimer, this, &APlatformerGameMode::LoadNextLevel, EndGameLength, false);//starts the five second timer to start the next level
	else GetWorld()->GetTimerManager().SetTimer(EndOfGameTimer, this, &APlatformerGameMode::ReloadLevel1, EndGameLength, false);//starts the five second timer to start the first 
	
}

bool APlatformerGameMode::GetGameState()
{//returns if the game is ongoing 
	return InGame;
}

bool APlatformerGameMode::GetWinState()
{//returns if the game is a win or lose
	return winner;
}

float APlatformerGameMode::CoinPercent()
{
	MaxCoints = totalCoins + coinsFound;//gets the total of coins found and remaining 
	return (coinsFound / MaxCoints) * percMulti;//calculates the percentage of found coins 
}

void APlatformerGameMode::ReduceLives()
{
	Lives--;//decreases the lives by one 
	if (Lives <= zero)//if less than or equal to zero
	{
		GameOver(false);//ends game and sets the winstate to lose 
		Lives = zero;
	}

}

int APlatformerGameMode::GetLives()
{//returns the amount of lives 
	return Lives;
}

void APlatformerGameMode::LoadNextLevel()
{
	UGameplayStatics::OpenLevel(GetWorld(), "MainLevel");//opens the second level
}

void APlatformerGameMode::ReloadLevel1()
{
	UGameplayStatics::OpenLevel(GetWorld(), "TutorialLevel");//opens the first level
}
