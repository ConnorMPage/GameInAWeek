// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "Blueprint/UserWidget.h"
#include "ThePlayerController.generated.h"
class APlatformerGameMode;
/**
 * 
 */
UCLASS()
class GAMEINAWEEK_API AThePlayerController : public APlayerController
{
	GENERATED_BODY()
protected:
	virtual void BeginPlay() override;
public:
	virtual void Tick(float DeltaTime) override;
	UFUNCTION(BlueprintPure)
	int GetCoinsLeft();
	UFUNCTION(BlueprintPure)
	int GetCoinsFound();
private:
	UPROPERTY(VisibleAnywhere)
	APlatformerGameMode* GameModeRef;
	
	UPROPERTY()
	int coinsFound = 0;
	UPROPERTY()
	int coinsLeft = 0;

	UPROPERTY(EditAnywhere)
	TSubclassOf<UUserWidget> PlayerHudClass;
	UPROPERTY()
	UUserWidget* PlayerHudUI;
	UPROPERTY(EditAnywhere)
	TSubclassOf<UUserWidget> CrosshairClass;
	UPROPERTY()
	UUserWidget* CrosshairUI;

	
};
