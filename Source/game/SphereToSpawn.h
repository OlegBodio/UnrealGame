// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SphereToSpawn.generated.h"

UCLASS()
class GAME_API ASphereToSpawn : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ASphereToSpawn();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
		void NormalizeCollisionSphere();

		static void IncreaseSpeed();

	UFUNCTION()
		void Move(float DeltaTime);

	UFUNCTION()
		static void SetSpeed(float Value = 150.0f);

protected:

	UPROPERTY(EditAnyWhere, BlueprintReadWrite)
		class USphereComponent* CollisionSphere;

		static float SphereSize;

		static float Speed;

	UFUNCTION()
		void OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor,
			UPrimitiveComponent* OtherComponent, int32 OtherBoduIndex,
			bool bFromSweep, const FHitResult& Hit);
	

};