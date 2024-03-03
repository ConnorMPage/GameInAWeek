// Fill out your copyright notice in the Description page of Project Settings.


#include "PlatformerGameMode.h"

void APlatformerGameMode::AddCoinToTotal()
{
	totalCoins++;
}

void APlatformerGameMode::coinFound()
{
	coinsFound++;
	totalCoins--;
}

int APlatformerGameMode::GetCoinTotal()
{
	return totalCoins;
}

int APlatformerGameMode::GetCoinsFound()
{
	return coinsFound;
}

void APlatformerGameMode::setCheckpoint(FVector checkpointPos)
{
	CurrentCheckpoint = checkpointPos;
}

FVector APlatformerGameMode::GetCheckpoint()
{
	return CurrentCheckpoint;
}

void APlatformerGameMode::GameOver(bool Complete)
{
	InGame = false;
	winner = Complete;
}

bool APlatformerGameMode::GetGameState()
{
	return InGame;
}

bool APlatformerGameMode::GetWinState()
{
	return winner;
}

float APlatformerGameMode::CoinPercent()
{
	MaxCoints = totalCoins + coinsFound;
	return (coinsFound / MaxCoints) * percMulti;
}
