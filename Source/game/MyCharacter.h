// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"

#include "Bullet.h"

#include "Animation/AnimInstance.h"
#include "Kismet/GameplayStatics.h"

#include "MyCharacter.generated.h"

UCLASS()
class GAME_API AMyCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AMyCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
public:
	UPROPERTY(VisibleDefaultsOnly, Category = Mesh) 
		class USkeletalMeshComponent* HandsMesh;

	UPROPERTY(VisibleDefaultsOnly, Category = Mesh)
		class USkeletalMeshComponent* GunMesh;

	UPROPERTY(VisibleDefaultsOnly, Category = Mesh)
		class USceneComponent* MuzzleLocation;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
		class UCameraComponent* FirstPersonCamera;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = Camera)
		float TurnRate;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = Camera)
		float LookUpRate; 

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
		FVector GunOffSet;


protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		float HP = 100.0f;// Health points of player

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		int SpheresDestoyedCount = 0;// Count of destroyed spheres

	void onFire();// function is being called when we try to fire

	void moveForward(float value);//moving
	void moveRight(float value);//moving

	void turnAtRate(float rate);//moving
	void lookAtRate(float rate);//moving


	

public:

	UPROPERTY(EditDefaultsOnly, Category = Projectile)
		TSubclassOf<class ABullet> Bullet;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
		class USoundBase* FireSound;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
		class UAnimMontage* FireAnimation;

	UFUNCTION()
	void TakeDamage(float Value = 20.0f);// function that deal damage to character

	UFUNCTION()
		void AddDestroyedSphere();//this function adds destroyed sphere


	class UAnimInstance* AnimInstance;

	class UWorld* World;

	FRotator SpawnRotation;
	FVector SpawnLocation;
};
