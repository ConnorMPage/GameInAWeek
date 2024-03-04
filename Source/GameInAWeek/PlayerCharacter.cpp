// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"

// Sets default values
APlayerCharacter::APlayerCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	GetMesh()->SetNotifyRigidBodyCollision(true);

	SpringArmForMainCam = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraAttachmentArm"));
	SpringArmForMainCam->SetupAttachment(FindComponentByClass<USkeletalMeshComponent>()); // attaches to the character mesh

	//create camera
	MainCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	MainCamera->SetupAttachment(SpringArmForMainCam);//attaches to spring arm

	//sets spring arm values
	SpringArmForMainCam->TargetArmLength = SpringArmLength;
	SpringArmForMainCam->SetRelativeLocation(SpringArmLocation);
	//sets camera values
	MainCamera->SetRelativeLocation(OriginalCamLocation);
	MainCamera->SetRelativeRotation(OriginalCamRotation);
	
}

// Called when the game starts or when spawned
void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (Climbing)
	{
		Climbing = ClimbLineTrace();
		if (!Climbing)
		{
			GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_Falling);
			SetActorRotation(FRotator(0.0f,0.0f,0.0f));
		}

	}
}

// Called to bind functionality to input
void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent->BindAxis(TEXT("ForwardMovement"), this, &APlayerCharacter::ForwardMovement);
	PlayerInputComponent->BindAxis(TEXT("Strafe"), this, &APlayerCharacter::Strafe);
	PlayerInputComponent->BindAxis(TEXT("LookUp"), this, &APlayerCharacter::LookUp);
	PlayerInputComponent->BindAxis(TEXT("Turn"), this, &APlayerCharacter::Turn);
	//action bindings
	PlayerInputComponent->BindAction(TEXT("Jump"), IE_Pressed, this, &APlayerCharacter::Jump);
	PlayerInputComponent->BindAction(TEXT("Crouch"), IE_Pressed, this, &APlayerCharacter::StartCrouch);
	PlayerInputComponent->BindAction(TEXT("Crouch"), IE_Released, this, &APlayerCharacter::EndCrouch);
	PlayerInputComponent->BindAction(TEXT("Dash"), IE_Pressed, this, &APlayerCharacter::Dash);
	PlayerInputComponent->BindAction(TEXT("Climb"), IE_Pressed, this, &APlayerCharacter::Climb);
	PlayerInputComponent->BindAction(TEXT("LeftDash"), IE_Pressed, this, &APlayerCharacter::LeftDash);
	PlayerInputComponent->BindAction(TEXT("RightDash"), IE_Pressed, this, &APlayerCharacter::RightDash);
}


//movement functions
void APlayerCharacter::ForwardMovement(float AxisAmount)
{
	if(!Climbing)AddMovementInput(GetActorForwardVector() * AxisAmount);
	else AddMovementInput(GetActorUpVector() * AxisAmount);
}

void APlayerCharacter::Strafe(float AxisAmount)
{
	AddMovementInput(GetActorRightVector() * AxisAmount);
}

void APlayerCharacter::LookUp(float AxisAmount)
{
	AddControllerPitchInput(AxisAmount);
}

void APlayerCharacter::Turn(float AxisAmount)
{
	if(!Climbing)AddControllerYawInput(AxisAmount);
}

//special movment functions
void APlayerCharacter::StartCrouch()
{
	APlayerCharacter::Crouch();
}

void APlayerCharacter::EndCrouch()
{
	APlayerCharacter::UnCrouch();
}

void APlayerCharacter::Dash()
{
	if(!Climbing)LaunchCharacter(GetActorForwardVector() * DashSpeed, false, false);
}

void APlayerCharacter::Climb()
{

	if (!Climbing)Climbing = ClimbLineTrace();
	else
	{
		Climbing = false;
		GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_Falling);
	}
	if (Climbing)
	{
		GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_Flying);
		FRotator currentRot = GetActorRotation();
		SetActorRotation(FRotator(currentRot.Roll, currentRot.Pitch, wallRot.Yaw + WallRotAdd));
	}

}

void APlayerCharacter::LeftDash()
{
	LaunchCharacter(GetActorRightVector() * -DashSpeed, false, false);
}

void APlayerCharacter::RightDash()
{
	LaunchCharacter(GetActorRightVector() * DashSpeed, false, false);
}

bool APlayerCharacter::ClimbLineTrace()
{
	AController* ControllerRef = GetController();//gets the controller
	FVector CamLocation;//camera location
	FRotator CamRotation;//camera rotation
	ControllerRef->GetPlayerViewPoint(CamLocation, CamRotation);//uses the location and rotation to get the cameras viewpoint 
	FVector End = CamLocation + CamRotation.Vector() * CastRange;// gets the end point for a LineTrace

	FHitResult Hit;
	bool bTargetHit = GetWorld()->LineTraceSingleByChannel(Hit, CamLocation, End, ECC_Visibility);
	if (bTargetHit) {
		
		wallRot = Hit.Normal.Rotation();
		
	}
	return bTargetHit;
}



