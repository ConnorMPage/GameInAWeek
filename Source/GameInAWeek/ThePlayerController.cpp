// Fill out your copyright notice in the Description page of Project Settings.


#include "ThePlayerController.h"
#include <Kismet/GameplayStatics.h>
#include "PlatformerGameMode.h"
void AThePlayerController::BeginPlay()
{
	GameModeRef = Cast<APlatformerGameMode>(UGameplayStatics::GetGameMode(GetWorld()));//casts to the gamemode
	Super::BeginPlay();

	CrosshairUI = CreateWidget(this, CrosshairClass);
	if (CrosshairUI != nullptr)CrosshairUI->AddToViewport();//adds the crosshair to the viewport

	PlayerHudUI = CreateWidget(this, PlayerHudClass);
	if (PlayerHudUI != nullptr)PlayerHudUI->AddToViewport();//adds the HUD to the viewport 
}

void AThePlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	coinsLeft = GameModeRef->GetCoinTotal();
	coinsFound = GameModeRef->GetCoinsFound();
	LivesLeft = GameModeRef->GetLives();
	if (!GameModeRef->GetGameState())EndofGame();
}

int AThePlayerController::GetCoinsLeft()
{//returns value for blueprint pure function
	return coinsLeft;
}

int AThePlayerController::GetCoinsFound()
{//returns value for blueprint pure function
	return coinsFound;
}

float AThePlayerController::GetCoinsPerc()
{//returns value for blueprint pure function
	return WinPerc;
}

float AThePlayerController::GetLives()
{//returns value for blueprint pure function
	return LivesLeft;
}

void AThePlayerController::EndofGame()
{
	
	if (GameModeRef->GetWinState())//if game won
	{
		WinPerc = GameModeRef->CoinPercent();
		if (WinPerc < oneStar)//if not one star under 25%
		{
			WinUI = CreateWidget(this, WinClass);
			if (WinUI != nullptr)WinUI->AddToViewport();
		}
		else if (WinPerc >= oneStar && WinPerc < twoStar)//one star over 25% under 50%
		{
			Win1UI = CreateWidget(this, Win1Class);
			if (Win1UI != nullptr)Win1UI->AddToViewport();
		}
		else if (WinPerc >= twoStar && WinPerc < threeStar)//two star over 50% under 75%
		{
			Win2UI = CreateWidget(this, Win2Class);
			if (Win2UI != nullptr)Win2UI->AddToViewport();
		}
		else if (WinPerc >= threeStar)//three star over 75%
		{
			Win3UI = CreateWidget(this, Win3Class);
		
			if (Win3UI != nullptr)Win3UI->AddToViewport();
		}

	}
	else//lost game
	{
		WinPerc = GameModeRef->CoinPercent();
		LossUI = CreateWidget(this, LossClass);
		if (LossUI != nullptr)LossUI->AddToViewport();
	}
}
