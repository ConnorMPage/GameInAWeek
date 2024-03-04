// Fill out your copyright notice in the Description page of Project Settings.


#include "Checkpoint.h"
#include <Kismet/GameplayStatics.h>
#include "PlatformerGameMode.h"


// Sets default values
ACheckpoint::ACheckpoint()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	CheckpointMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Checkpoint Mesh"));//creates mesh


	CollisionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("Collision Box"));//creates collision box
	CollisionBox->SetupAttachment(CheckpointMesh);
	CollisionBox->SetBoxExtent(BoxExtentSize);//sets box size
	CollisionBox->SetRelativeLocation(BoxLocation);//sets box location
	CollisionBox->SetCollisionProfileName("Trigger");//sets collision profile
}

// Called when the game starts or when spawned
void ACheckpoint::BeginPlay()
{
	GameModeRef = Cast<APlatformerGameMode>(UGameplayStatics::GetGameMode(GetWorld()));//cast to gamemode 
	Super::BeginPlay();
	CollisionBox->OnComponentBeginOverlap.AddDynamic(this, &ACheckpoint::OnOverlapBegin);//overlap dynamic 
	if (isStart)SetNewCheckpoint(this->GetActorLocation());//if its the start point set the current checkpoint 
}

// Called every frame
void ACheckpoint::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ACheckpoint::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	SetNewCheckpoint(this->GetActorLocation());//sets teh new checkpoint to the checkpoints position 
	if (isFinish)GameModeRef->GameOver(true);
}

void ACheckpoint::SetNewCheckpoint(FVector Pos)
{
	GameModeRef->setCheckpoint(Pos);//sets the current checkpoint in gamemode 
}

