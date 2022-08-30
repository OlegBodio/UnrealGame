// Fill out your copyright notice in the Description page of Project Settings.
#include "SphereSpawner.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/Character.h"




// Sets default values
ASphereSpawner::ASphereSpawner()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("DefaultSceneRoot"));
	SpawnVolume = CreateDefaultSubobject<UBoxComponent>(TEXT("SpawnVolume"));
	SpawnVolume->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
	
	
	AxisVector = FVector(0, 0, 1);
}

// Called when the game starts or when spawned
void ASphereSpawner::BeginPlay()
{
	Super::BeginPlay();
	Wave();
	
}

// Called every frame
void ASphereSpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (SpheresInWave.Num() <= (SpheresIn1500 - 10))
	{
		Wave(SpheresInWaveNum, SpawnRadius);
	}
}

void ASphereSpawner::SpawnSphere(int SphereNum, int Distance)
{
	FVector Dimensions = FVector(std::rand() % Distance, 0, 1000);

	ACharacter* myCharacter = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
	FVector SpawnLocation = myCharacter->GetActorLocation();
	AngleAxis += std::rand() % 360;

	FVector RotateValue = Dimensions.RotateAngleAxis(AngleAxis, AxisVector);
	SpawnLocation += RotateValue;

	FRotator SpawnRotation = FRotator(0, AngleAxis, 0);

	FQuat QuatRotation = FQuat(SpawnRotation);
	SetActorLocationAndRotation(SpawnLocation, QuatRotation, false, 0, ETeleportType::None);

	FActorSpawnParameters ActorSpawnParams;
	ActorSpawnParams.SpawnCollisionHandlingOverride =
		ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButDontSpawnIfColliding;

	ASphereToSpawn* NewSphere = (ASphereToSpawn*)(GetWorld()->SpawnActor<ASphereToSpawn>(Sphere, SpawnLocation, SpawnRotation, ActorSpawnParams));

	if (NewSphere)
	{
		NewSphere->NormalizeCollisionSphere();
		if (Dimensions.X <= 1500)
		{
			SpheresInWave.Add(NewSphere);
		}
	}
	
}

void ASphereSpawner::DestroySphere(ASphereToSpawn* SpherePtr)
{
	SpheresInWave.Remove(SpherePtr);
	SpherePtr->Destroy();
}

void ASphereSpawner::Wave(int SphereNum, float Distance)
{
	SpheresInWave.Empty();
	
	for (int i = 0; i < 10; ++i)
	{
		SpawnSphere();
	}
	for (int i = 0; i < SphereNum - 10; ++i)
	{
		SpawnSphere(SphereNum - 10, Distance);
	}
	SpheresIn1500 = SpheresInWave.Num();
	SpheresInWaveNum = SpheresInWaveNum + SpheresInWaveNum * 0.1;
	SpawnRadius += SpawnRadius * 0.1;
	ASphereToSpawn::IncreaseSpeed();
	++WavesNum;
}



