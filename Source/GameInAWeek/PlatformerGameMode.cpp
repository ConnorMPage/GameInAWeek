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
