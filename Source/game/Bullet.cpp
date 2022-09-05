// Fill out your copyright notice in the Description page of Project Settings.


#include "Bullet.h"
#include "SphereToSpawn.h"
#include "SphereSpawner.h"
#include "MyCharacter.h"
#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Kismet/GameplayStatics.h"

//#include "Sphere.h"

// Sets default values
ABullet::ABullet()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	CollisionSphere = CreateDefaultSubobject<USphereComponent>(TEXT("Sphere Collision"));
	CollisionSphere->InitSphereRadius(BulletSize);

	RootComponent = CollisionSphere;

	BulletMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("Bullet Movemennt"));
	BulletMovement->UpdatedComponent = CollisionSphere;
	BulletMovement->ProjectileGravityScale = 0.0f;// bullet should ignore physic and move forward only
	BulletMovement->InitialSpeed = BulletInitialSpeed;
	BulletMovement->MaxSpeed = BulletMaxSpeed;
	BulletMovement->bRotationFollowsVelocity = true;
	BulletMovement->bShouldBounce = true;

	InitialLifeSpan = 3.0f;


}

// Called when the game starts or when spawned
void ABullet::BeginPlay()
{
	Super::BeginPlay();
	CollisionSphere->OnComponentBeginOverlap.AddDynamic(this, &ABullet::OnHit);// When sphere hits a player will be called OnHit method
}

// Called every frame
void ABullet::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ABullet::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComponent, int32 OtherBoduIndex, bool bFromSweep, const FHitResult& Hit)
{
	ASphereToSpawn* SpherePtr = Cast<ASphereToSpawn>(OtherActor);
	if (SpherePtr)// if Bullet hits the sphere
	{
		ASphereSpawner* SphereSpawner = (ASphereSpawner*)(UGameplayStatics::GetActorOfClass(GetWorld(), ASphereSpawner::StaticClass()));
		SphereSpawner->DestroySphere(SpherePtr);//Call Sphere Spawner to destroy sphere
		AMyCharacter* MyCharacter = (AMyCharacter*)UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
		MyCharacter->AddDestroyedSphere();//add destoyed sphere to character counter
		Destroy();// destroy self
	}
}

