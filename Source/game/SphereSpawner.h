// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "Components/BoxComponent.h"
#include "Kismet/GameplayStatics.h"
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SphereToSpawn.h"
#include "SphereSpawner.generated.h"

UCLASS()
class GAME_API ASphereSpawner : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASphereSpawner();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
		void SpawnSphere(int SphereNum = 10, int Distance = 1500);

	float AngleAxis;

	UPROPERTY(EditDefaultsOnly, Category = SpawnLocation)
		FVector AxisVector;

	

	UFUNCTION()
		void DestroySphere(ASphereToSpawn* SpherePtr);

	
protected:

	UPROPERTY(EditDefaultsOnly, Category = Sphere)
		TSubclassOf<class ASphereToSpawn> Sphere;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		class UBoxComponent* SpawnVolume;

	UPROPERTY(EditDefaultsOnly, Category = WaveParameters)
		int32 SpheresInWaveNum = 15;

	UPROPERTY(VisibleAnywhere, Category = WaveParameters)
		int32 SpheresIn1500 = 0;

	UPROPERTY(EditDefaultsOnly, Category = SpawnLocation)
		float SpawnRadius = 2000;

	void Wave(int SphereNum = 15, float Distance = 2000);

	UPROPERTY(VisibleAnywhere, Category = SpawnLocation)
		TArray<ASphereToSpawn*> SpheresInWave;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Waves)
		int WavesNum = 0;

};
