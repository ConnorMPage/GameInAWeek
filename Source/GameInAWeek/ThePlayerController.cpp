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
}

int AThePlayerController::GetCoinsLeft()
{
	return coinsLeft;
}

int AThePlayerController::GetCoinsFound()
{
	return coinsFound;
}
