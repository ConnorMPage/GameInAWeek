// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "PlatformerGameMode.generated.h"

/**
 * 
 */
UCLASS()
class GAMEINAWEEK_API APlatformerGameMode : public AGameModeBase
{
	GENERATED_BODY()
	

public:

	//public getter and setter functions 
	UFUNCTION()
	void AddCoinToTotal();
	UFUNCTION()
	void coinFound();
	UFUNCTION()
	int GetCoinTotal();
	UFUNCTION()
	int GetCoinsFound();
	UFUNCTION()
	void setCheckpoint(FVector checkpointPos);
	UFUNCTION()
	FVector GetCheckpoint();
	UFUNCTION()
	void GameOver(bool Complete);
	UFUNCTION()
	bool GetGameState();
	UFUNCTION()
	bool GetWinState();
	UFUNCTION()
	float CoinPercent();
	UFUNCTION()
	void ReduceLives();
	UFUNCTION()
	int GetLives();

private:
	UPROPERTY()
	bool InGame = true;
	UPROPERTY()
	bool winner = false;
	UPROPERTY()
	FVector CurrentCheckpoint;
	UPROPERTY()
	int totalCoins = 0;
	UPROPERTY()
	int coinsFound = 0;
	UPROPERTY()
	int MaxCoints = 0;

	UPROPERTY(EditAnywhere)
	int Lives = 5;

	const int zero = 0;
	const int percMulti = 100;
	

	//end of game functions and timer
	UFUNCTION()
	void LoadNextLevel();

	UFUNCTION()
	void ReloadLevel1();

	UPROPERTY(EditAnywhere)
	float EndGameLength = 5.0f;
	FTimerHandle EndOfGameTimer;
};
