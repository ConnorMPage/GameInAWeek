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
	void GameOver();
private:
	
	UPROPERTY()
	FVector CurrentCheckpoint;
	UPROPERTY()
	int totalCoins = 0;
	UPROPERTY()
	int coinsFound = 0;
};
