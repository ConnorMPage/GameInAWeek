// Fill out your copyright notice in the Description page of Project Settings.


#include "Coin.h"
#include "PlatformerGameMode.h"
// Sets default values
ACoin::ACoin()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	coinMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Coin Mesh"));//creates mesh
	SetRootComponent(coinMesh);//sets mesh as root
	coinMesh->SetNotifyRigidBodyCollision(true);

}

// Called when the game starts or when spawned
void ACoin::BeginPlay()
{
	Super::BeginPlay();
	OnActorHit.AddDynamic(this, &ACoin::OnHit);
	GameModeRef = Cast<APlatformerGameMode>(UGameplayStatics::GetGameMode(GetWorld()));
	GameModeRef->AddCoinToTotal();
}

// Called every frame
void ACoin::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	AddActorLocalRotation(FRotator(0.f, spinSpeed * DeltaTime, 0.f));
}

void ACoin::OnHit(AActor* SelfActor, AActor* OtherActor, FVector NormalImpulse, const FHitResult& Hit)
{
	GameModeRef->coinFound();
	Destroy();
}

