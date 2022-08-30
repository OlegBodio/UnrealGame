// Fill out your copyright notice in the Description page of Project Settings.


#include "SphereToSpawn.h"
#include "SphereSpawner.h"
#include "MyCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "Components/SphereComponent.h"
#include "Particles/ParticleSystemComponent.h"

// Sets default values
ASphereToSpawn::ASphereToSpawn()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CollisionSphere = CreateDefaultSubobject<USphereComponent>(TEXT("Sphere"));
	CollisionSphere->InitSphereRadius(SphereSize);

	RootComponent = CollisionSphere;

	CollisionSphere->SetSimulatePhysics(true);
	CollisionSphere->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);

	CollisionSphere->SetSphereRadius(SphereSize + 80);

}

// Called when the game starts or when spawned
void ASphereToSpawn::BeginPlay()
{
	Super::BeginPlay();
	CollisionSphere->OnComponentBeginOverlap.AddDynamic(this, &ASphereToSpawn::OnHit);
}

// Called every frame
void ASphereToSpawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	Move(DeltaTime);
}

float ASphereToSpawn::SphereSize = 16.0f;

float ASphereToSpawn::Speed = 150.0f;
 
void ASphereToSpawn::NormalizeCollisionSphere()
{
	CollisionSphere->SetSphereRadius(SphereSize);
}

void ASphereToSpawn::IncreaseSpeed()
{
	if (Speed < 347)
	{
		Speed += Speed * 0.1;
	}

}

void ASphereToSpawn::Move(float DeltaTime)
{
	ACharacter* myCharacter = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
	if (myCharacter)
	{
		FVector Dir = (myCharacter->GetActorLocation() - GetActorLocation()).GetSafeNormal();
		Dir *= (Speed * DeltaTime);
		SetActorLocation(GetActorLocation() + Dir);
	}
}

void ASphereToSpawn::SetSpeed(float Value)
{
	Speed = Value;
}

void ASphereToSpawn::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComponent, int32 OtherBoduIndex, bool bFromSweep, const FHitResult& Hit)
{
	AMyCharacter* CharacterPtr = Cast<AMyCharacter>(OtherActor);
	if (CharacterPtr)
	{
		ASphereSpawner* SphereSpawner = (ASphereSpawner*)(UGameplayStatics::GetActorOfClass(GetWorld(), ASphereSpawner::StaticClass()));
		CharacterPtr->TakeDamage();
		SphereSpawner->DestroySphere(this);
	}
}