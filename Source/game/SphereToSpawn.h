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
		void NormalizeCollisionSphere();// This method is described in SphereToSpawn.cpp

		static void IncreaseSpeed();// This method makes sphere to move faster

	UFUNCTION()
		void Move(float DeltaTime);// this function moves sphere in world

	UFUNCTION()
		static void SetSpeed(float Value = 150.0f);// Sets speed of moving sphere in world

protected:

	UPROPERTY(EditAnyWhere, BlueprintReadWrite)
		class USphereComponent* CollisionSphere;

		static float SphereSize;// This is static variable that contains size of collision sphere

		static float Speed;// This is static variable that contains speed of sphere moving

		static float SpeedLimit;// This is static variable that contains speed limit of sphere moving

	UFUNCTION()
		void OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor,
			UPrimitiveComponent* OtherComponent, int32 OtherBoduIndex,
			bool bFromSweep, const FHitResult& Hit);//this function works when sphere collides with any objects
	

};