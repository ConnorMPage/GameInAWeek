// Fill out your copyright notice in the Description page of Project Settings.


#include "ThePlayerController.h"
#include <Kismet/GameplayStatics.h>
#include "PlatformerGameMode.h"
void AThePlayerController::BeginPlay()
{
	GameModeRef = Cast<APlatformerGameMode>(UGameplayStatics::GetGameMode(GetWorld()));
	Super::BeginPlay();

	CrosshairUI = CreateWidget(this, CrosshairClass);
	if (CrosshairUI != nullptr)CrosshairUI->AddToViewport();

	PlayerHudUI = CreateWidget(this, PlayerHudClass);
	if (PlayerHudUI != nullptr)PlayerHudUI->AddToViewport();


	



}

void AThePlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	coinsLeft = GameModeRef->GetCoinTotal();
	coinsFound = GameModeRef->GetCoinsFound();
	LivesLeft = GameModeRef->GetLives();
	if (GameModeRef->GetGameState())EndofGame();
}

int AThePlayerController::GetCoinsLeft()
{
	return coinsLeft;
}

int AThePlayerController::GetCoinsFound()
{
	return coinsFound;
}

float AThePlayerController::GetCoinsPerc()
{
	return WinPerc;
}

float AThePlayerController::GetLives()
{
	return LivesLeft;
}

void AThePlayerController::EndofGame()
{
	if (GameModeRef->GetWinState())
	{
		WinPerc = GameModeRef->CoinPercent();
		if (WinPerc < oneStar)
		{
			WinUI = CreateWidget(this, WinClass);
			if (WinUI != nullptr)WinUI->AddToViewport();
		}
		else if (WinPerc >= oneStar && WinPerc < twoStar)
		{
			Win1UI = CreateWidget(this, Win1Class);
			if (Win1UI != nullptr)Win1UI->AddToViewport();
		}
		else if (WinPerc >= twoStar && WinPerc < threeStar)
		{
			Win2UI = CreateWidget(this, Win2Class);
			if (Win2UI != nullptr)Win2UI->AddToViewport();
		}
		else if (WinPerc >= threeStar)
		{
			Win3UI = CreateWidget(this, Win3Class);
		
			if (Win3UI != nullptr)Win3UI->AddToViewport();
		}

	}
	else
	{
		LossUI = CreateWidget(this, LossClass);
		if (LossUI != nullptr)LossUI->AddToViewport();
	}
}
