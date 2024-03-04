// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Kismet/GameplayStatics.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"
#include "Coin.generated.h"
class APlatformerGameMode;
UCLASS()
class GAMEINAWEEK_API ACoin : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACoin();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* coinMesh;
	UPROPERTY(EditAnywhere)
	float spinSpeed = 35.0f;

	UPROPERTY(VisibleAnywhere)
	APlatformerGameMode* GameModeRef;
	UFUNCTION()
	void OnHit(AActor* SelfActor, AActor* OtherActor, FVector NormalImpulse,
		const FHitResult& Hit);
};
