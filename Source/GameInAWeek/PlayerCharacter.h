// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "PlayerCharacter.generated.h"

UCLASS()
class GAMEINAWEEK_API APlayerCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	APlayerCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;


private:

//basic movement functions
	UFUNCTION()
	void ForwardMovement(float AxisAmount);
	UFUNCTION()
	void Strafe(float AxisAmount);
	UFUNCTION()
	void LookUp(float AxisAmount);
	UFUNCTION()
	void Turn(float AxisAmount);

	//special movements 
	UFUNCTION()
	void StartCrouch();
	UFUNCTION()
	void EndCrouch();
	UFUNCTION()
	void Dash();

	UPROPERTY(EditAnywhere)
	UCameraComponent* MainCamera;
	UPROPERTY(EditAnywhere)
	USpringArmComponent* SpringArmForMainCam;

	UPROPERTY(VisibleAnywhere)
	FVector OriginalCamLocation = FVector(0.85f, 60.0f, 132.58f);//original camera location
	UPROPERTY(VisibleAnyWhere)
	FRotator OriginalCamRotation = FRotator(0, -25, 0);//Original Camera Rotation

	UPROPERTY(VisibleAnywhere)
	FVector SpringArmLocation = FVector(0.0f, 0.0f, 90.0f);//location of the spring arm
	UPROPERTY(VisibleAnywhere)
	float SpringArmLength = 200.0f;//Length of Springarm
};
