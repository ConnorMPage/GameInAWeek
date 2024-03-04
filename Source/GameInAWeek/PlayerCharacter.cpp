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
	if (Climbing)//chercks if currently climbing 
	{
		Climbing = ClimbLineTrace();//if climbing check if still close enough to a wall surface 
		if (!Climbing)//if no longer climbing 
		{
			GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_Falling);//sets move state to falling but once the player touches the ground it is auto set to walking 
			SetActorRotation(FRotator(0.0f,0.0f,0.0f));//resets rotation 
		}

	}
}

// Called to bind functionality to input
void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	//movment bindings 
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
	if(!Climbing)AddMovementInput(GetActorForwardVector() * AxisAmount);//if not climbing move forward backwards 
	else AddMovementInput(GetActorUpVector() * AxisAmount);//if climbing then move up and down 
}

void APlayerCharacter::Strafe(float AxisAmount)
{
	AddMovementInput(GetActorRightVector() * AxisAmount);//left and right movement 
}

void APlayerCharacter::LookUp(float AxisAmount)
{
	AddControllerPitchInput(AxisAmount);//look up and down 
}

void APlayerCharacter::Turn(float AxisAmount)
{
	if(!Climbing)AddControllerYawInput(AxisAmount); // rotate side to side, if climbing this is disabled
}

//special movment functions
void APlayerCharacter::StartCrouch()
{
	APlayerCharacter::Crouch();// would work but no aniamtion is set up
}

void APlayerCharacter::EndCrouch()
{
	APlayerCharacter::UnCrouch();// would work but no aniamtion is set u
}

void APlayerCharacter::Dash()
{
	if(!Climbing)LaunchCharacter(GetActorForwardVector() * DashSpeed, false, false);//launches the character on its forward vector 
}

void APlayerCharacter::Climb()
{

	if (!Climbing)Climbing = ClimbLineTrace();//if not already climbing then it will exectue a line trace 
	else//if already climbing and the climb button is pressed 
	{
		Climbing = false;//climbing is set to false 
		GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_Falling);//movement mode is set to falling 
	}
	if (Climbing)//if climbing is nnow enabled
	{
		GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_Flying);//movement mode is set to flying to deactivate gravity 
		FRotator currentRot = GetActorRotation();//gets the actors rotation
		SetActorRotation(FRotator(currentRot.Roll, currentRot.Pitch, wallRot.Yaw + WallRotAdd));//sets the characters rotation to be set towards the wall 
	}

}

void APlayerCharacter::LeftDash()
{
	LaunchCharacter(GetActorRightVector() * -DashSpeed, false, false);//launches the character using the right vector with a negative speed
}

void APlayerCharacter::RightDash()
{
	LaunchCharacter(GetActorRightVector() * DashSpeed, false, false);//launches the character to the right 
}

bool APlayerCharacter::ClimbLineTrace()
{
	AController* ControllerRef = GetController();//gets the controller
	FVector CamLocation;//camera location
	FRotator CamRotation;//camera rotation
	ControllerRef->GetPlayerViewPoint(CamLocation, CamRotation);//uses the location and rotation to get the cameras viewpoint 
	FVector End = CamLocation + CamRotation.Vector() * CastRange;// gets the end point for a LineTrace

	FHitResult Hit;
	bool bTargetHit = GetWorld()->LineTraceSingleByChannel(Hit, CamLocation, End, ECC_Visibility);//linetrace
	if (bTargetHit) {
		
		wallRot = Hit.Normal.Rotation();//gets the rotation of the hit object
		
	}
	return bTargetHit;//returns true if object is hit 
}



