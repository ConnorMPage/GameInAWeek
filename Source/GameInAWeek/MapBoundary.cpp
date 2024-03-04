// Fill out your copyright notice in the Description page of Project Settings.


#include "MapBoundary.h"
#include <Kismet/GameplayStatics.h>
#include "PlatformerGameMode.h"
// Sets default values
AMapBoundary::AMapBoundary()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	CollisionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("Collision Box"));//creates collision box
	CollisionBox->SetBoxExtent(BoxExtentSize);//sets box size
	CollisionBox->SetRelativeLocation(BoxLocation);//sets box location
	CollisionBox->SetCollisionProfileName("Trigger");//sets collision profile
}

// Called when the game starts or when spawned
void AMapBoundary::BeginPlay()
{
	GameModeRef = Cast<APlatformerGameMode>(UGameplayStatics::GetGameMode(GetWorld()));
	Super::BeginPlay();
	CollisionBox->OnComponentBeginOverlap.AddDynamic(this, &AMapBoundary::OnOverlapBegin);
}

// Called every frame
void AMapBoundary::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AMapBoundary::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	GameModeRef->ReduceLives();
	OtherActor->SetActorLocation(GameModeRef->GetCheckpoint());
}

