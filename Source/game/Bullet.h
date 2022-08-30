// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Bullet.generated.h"

UCLASS()
class GAME_API ABullet : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABullet();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(VisibleDefaultsOnly, Category = Projectile)
		class USphereComponent* CollisionSphere;

	UPROPERTY(VisibleAnyWhere, BlueprintReadOnly, Category = Movement)
		class UProjectileMovementComponent* BulletMovement;

	UFUNCTION()
		void OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor,
			UPrimitiveComponent* OtherComponent, int32 OtherBoduIndex,
			bool bFromSweep, const FHitResult& Hit);

	UPROPERTY(EditAnywhere)
		float DamageValue = 20.0f;

protected:

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		float BulletSize = 20.0f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		float BulletInitialSpeed = 3000.0f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		float BulletMaxSpeed = 3000.0f;
};
