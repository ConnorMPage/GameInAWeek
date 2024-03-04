// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/BoxComponent.h"
#include "TimePads.generated.h"



UCLASS()
class GAMEINAWEEK_API ATimePads : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATimePads();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	

private:
	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* TimePadMesh;

	UPROPERTY(EditAnywhere)
	float DefaultGameSpeed = 1.0f;


	UPROPERTY(EditAnywhere)
	float FastSpeed =3.0f ;

	UPROPERTY(EditAnywhere)
	float SlowSpeed = 0.5f;

	UPROPERTY(EditAnywhere)
	float NewGameSpeed;

	UPROPERTY(EditAnywhere)
	bool isFast = false;

	UPROPERTY(EditAnywhere)
	bool isSlow = false;
	UPROPERTY(EditAnywhere)
	bool isReset = false;

	UPROPERTY(EditAnywhere)
	UBoxComponent* CollisionBox;//creates collision box
	UPROPERTY(EditAnywhere)
	FVector BoxExtentSize = FVector(100.0f, 100.0f, 10.0f);//box size
	UPROPERTY(VisibleAnywhere)
	FVector BoxLocation = FVector(0.0f, 0.0f, 0.0f);//box location
	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
		UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
};
