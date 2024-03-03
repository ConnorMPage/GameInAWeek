// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/BoxComponent.h"
#include "Checkpoint.generated.h"
class APlatformerGameMode;
UCLASS()
class GAMEINAWEEK_API ACheckpoint : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACheckpoint();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
private:
	UPROPERTY(EditAnywhere)
	bool isStart = false;
	UPROPERTY(EditAnywhere)
	bool isFinish = false;
	UPROPERTY(VisibleAnywhere)
	APlatformerGameMode* GameModeRef;
	UPROPERTY(VisibleAnywhere)
	UBoxComponent* CollisionBox;//creates collision box
	UPROPERTY(EditAnywhere)
	FVector BoxExtentSize = FVector(100.0f, 100.0f, 10.0f);//box size
	UPROPERTY(VisibleAnywhere)
	FVector BoxLocation = FVector(0.0f, 0.0f, 0.0f);//box location
	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
		UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION()
	void SetNewCheckpoint(FVector Pos);
};
