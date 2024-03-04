// Fill out your copyright notice in the Description page of Project Settings.


#include "TimePads.h"
#include "Math/UnrealMathUtility.h"
#include "GameFramework/WorldSettings.h"
// Sets default values
ATimePads::ATimePads()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	TimePadMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Time Pad Mesh"));//creates mesh
	
	
	CollisionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("Collision Box"));//creates collision box
	CollisionBox->SetupAttachment(TimePadMesh);
	CollisionBox->SetBoxExtent(BoxExtentSize);//sets box size
	CollisionBox->SetRelativeLocation(BoxLocation);//sets box location
	CollisionBox->SetCollisionProfileName("Trigger");
}

// Called when the game starts or when spawned
void ATimePads::BeginPlay()
{
	Super::BeginPlay();
	CollisionBox->OnComponentBeginOverlap.AddDynamic(this, &ATimePads::OnOverlapBegin);//adds overlap dynamic 
}

// Called every frame
void ATimePads::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ATimePads::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if(isFast)NewGameSpeed = FastSpeed;
	if(isSlow)NewGameSpeed = SlowSpeed;
	if(isReset)NewGameSpeed = DefaultGameSpeed;

	if (isFast|| isSlow|| isReset)GetWorldSettings()->SetTimeDilation(NewGameSpeed);//if it is set to change time speed then it will change time dialation by the new speed 
		
	
	
	
	

}

