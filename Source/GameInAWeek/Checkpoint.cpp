// Fill out your copyright notice in the Description page of Project Settings.


#include "Checkpoint.h"
#include <Kismet/GameplayStatics.h>
#include "PlatformerGameMode.h"

// Sets default values
ACheckpoint::ACheckpoint()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	CollisionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("Collision Box"));//creates collision box
	CollisionBox->SetBoxExtent(BoxExtentSize);//sets box size
	CollisionBox->SetRelativeLocation(BoxLocation);//sets box location
	CollisionBox->SetCollisionProfileName("Trigger");//sets collision profile
}

// Called when the game starts or when spawned
void ACheckpoint::BeginPlay()
{
	GameModeRef = Cast<APlatformerGameMode>(UGameplayStatics::GetGameMode(GetWorld()));
	Super::BeginPlay();
	CollisionBox->OnComponentBeginOverlap.AddDynamic(this, &ACheckpoint::OnOverlapBegin);
	if (isStart)SetNewCheckpoint(this->GetActorLocation());
}

// Called every frame
void ACheckpoint::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ACheckpoint::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	SetNewCheckpoint(this->GetActorLocation());
	if (isFinish)GameModeRef->GameOver();
}

void ACheckpoint::SetNewCheckpoint(FVector Pos)
{
	GameModeRef->setCheckpoint(Pos);
}

