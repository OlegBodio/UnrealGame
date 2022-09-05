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

	CollisionSphere->SetSimulatePhysics(false);
	CollisionSphere->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);

	CollisionSphere->SetSphereRadius(SphereSize + 80);

}

// Called when the game starts or when spawned
void ASphereToSpawn::BeginPlay()
{
	Super::BeginPlay();
	CollisionSphere->OnComponentBeginOverlap.AddDynamic(this, &ASphereToSpawn::OnHit);// When sphere hits a player will be called OnHit method
}

// Called every frame
void ASphereToSpawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	Move(DeltaTime);// Sphere moves to player
}

float ASphereToSpawn::SphereSize = 16.0f;//default size of sphere

float ASphereToSpawn::Speed = 150.0f;//default speed of sphere

float ASphereToSpawn::SpeedLimit = 437.0f;//default speed limit of sphere
 
void ASphereToSpawn::NormalizeCollisionSphere()//this method should normallize size of collision sphere, 
//this is used and described in SphereSpawner.cpp in SpawnSphere function
{
	CollisionSphere->SetSphereRadius(SphereSize);
}

void ASphereToSpawn::IncreaseSpeed()//increase speed by 10%
{
	if (Speed < SpeedLimit)
	{
		Speed += Speed * 0.1;
	}

}

void ASphereToSpawn::Move(float DeltaTime)//sphere moves to Character every time
{
	ACharacter* myCharacter = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);// Find character in world
	if (myCharacter)
	{
		FVector Dir = (myCharacter->GetActorLocation() - GetActorLocation()).GetSafeNormal();//set sphere direction of moving
		Dir *= (Speed * DeltaTime);//set step by delta time and speed
		SetActorLocation(GetActorLocation() + Dir);// move sphere to mew location
	}
}

void ASphereToSpawn::SetSpeed(float Value)
{
	Speed = Value;
}

void ASphereToSpawn::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComponent, int32 OtherBoduIndex, bool bFromSweep, const FHitResult& Hit)
{
	AMyCharacter* CharacterPtr = Cast<AMyCharacter>(OtherActor);
	if (CharacterPtr)// is Sphere hits Character
	{
		ASphereSpawner* SphereSpawner = 
			(ASphereSpawner*)(UGameplayStatics::GetActorOfClass(GetWorld(), ASphereSpawner::StaticClass()));// find sphere spawner in world
		CharacterPtr->TakeDamage();//Character takes damage
		SphereSpawner->DestroySphere(this);// Sphere Spawner destroys this sphere and pointer to sphere 
	}
}