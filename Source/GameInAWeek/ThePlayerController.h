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
	//blueprint pure getter functions 
	UFUNCTION(BlueprintPure)
	int GetCoinsLeft();
	UFUNCTION(BlueprintPure)
	int GetCoinsFound();
	UFUNCTION(BlueprintPure)
	float GetCoinsPerc();
	UFUNCTION(BlueprintPure)
	float GetLives();
private:
	UPROPERTY(VisibleAnywhere)
	APlatformerGameMode* GameModeRef;//game mode reference 

	//hud variables 
	UPROPERTY()
	int LivesLeft;
	UPROPERTY()
	int coinsFound = 0;
	UPROPERTY()
	int coinsLeft = 0;
	UPROPERTY()
	float WinPerc;
	UPROPERTY()
	float oneStar = 25.0f;
	UPROPERTY()
	float twoStar = 50.0f;
	UPROPERTY()
	float threeStar = 75.0f;


	//widgets 
	UPROPERTY(EditAnywhere)
	TSubclassOf<UUserWidget> PlayerHudClass;
	UPROPERTY()
	UUserWidget* PlayerHudUI;
	UPROPERTY(EditAnywhere)
	TSubclassOf<UUserWidget> CrosshairClass;
	UPROPERTY()
	UUserWidget* CrosshairUI;

	UPROPERTY(EditAnywhere)
	TSubclassOf<UUserWidget> LossClass;
	UPROPERTY()
	UUserWidget* LossUI;
	UPROPERTY(EditAnywhere)
	TSubclassOf<UUserWidget> WinClass;
	UPROPERTY()
	UUserWidget* WinUI;
	UPROPERTY(EditAnywhere)
	TSubclassOf<UUserWidget> Win1Class;
	UPROPERTY()
	UUserWidget* Win1UI;
	UPROPERTY(EditAnywhere)
	TSubclassOf<UUserWidget> Win2Class;
	UPROPERTY()
	UUserWidget* Win2UI;
	UPROPERTY(EditAnywhere)
	TSubclassOf<UUserWidget> Win3Class;
	UPROPERTY()
	UUserWidget* Win3UI;


	UFUNCTION()
	void EndofGame();//runs the win/loss screens 
};
