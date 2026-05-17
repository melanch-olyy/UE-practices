// Fill out your copyright notice in the Description page of Project Settings.


#include "Spawner/ItemSpawner.h"
#include "Kismet/KismetMathLibrary.h"


// Sets default values
AItemSpawner::AItemSpawner()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	SpawnArea = CreateDefaultSubobject<UBoxComponent>(TEXT("Spawn Area"));
	
	MinSpawnDelay = 0.5f;
	MaxSpawnDelay = 2.5f;
}

// Called when the game starts or when spawned
void AItemSpawner::BeginPlay()
{
	Super::BeginPlay();
	
	StartSpawnTimer();
}

// Called every frame
void AItemSpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

FVector AItemSpawner::GetRandomSpawnPoint()
{
	const FVector SpawnOrigin = SpawnArea->Bounds.Origin;
	const FVector SpawnLimits = SpawnArea->Bounds.BoxExtent;
    
	return UKismetMathLibrary::RandomPointInBoundingBox(SpawnOrigin, SpawnLimits);
}

void AItemSpawner::SpawnActors()
{
	if(!ActorToSpawn || !GetWorld()) return;
	FActorSpawnParameters Parameters;
	Parameters.Owner = this;
	Parameters.Instigator = GetInstigator();
	Parameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;
	
	APickUpBase* SpawnActor = GetWorld()-> SpawnActor<APickUpBase>(ActorToSpawn, GetRandomSpawnPoint(),
		UKismetMathLibrary:: RandomRotator(), Parameters);
	
	StartSpawnTimer();
}

void AItemSpawner::StartSpawnTimer()
{
	RandomSpawnDelay = FMath::RandRange(MinSpawnDelay, MaxSpawnDelay);
	
	GetWorld()->GetTimerManager().SetTimer(SpawnTimerHandle, this,
		&AItemSpawner::SpawnActors, RandomSpawnDelay, false);
}
