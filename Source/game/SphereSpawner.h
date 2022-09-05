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
		void SpawnSphere(int SphereNum = 10, int Distance = 1500);//method that spawns some count of sphere in some radius around player  

	float AngleAxis;

	UPROPERTY(EditDefaultsOnly, Category = SpawnLocation)
		FVector AxisVector;

	

	UFUNCTION()
		void DestroySphere(ASphereToSpawn* SpherePtr);//method that destoys sphere

	
protected:

	UPROPERTY(EditDefaultsOnly, Category = Sphere)
		TSubclassOf<class ASphereToSpawn> Sphere;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		class UBoxComponent* SpawnVolume;

	UPROPERTY(EditDefaultsOnly, Category = WaveParameters)
		int32 SpheresInWaveNum = 15;//count of spheres in some wave. Default 15 spheres in first wave

	UPROPERTY(VisibleAnywhere, Category = WaveParameters)
		int32 SpheresIn1500 = 0;// Count sphere in radius 1500

	UPROPERTY(EditDefaultsOnly, Category = SpawnLocation)
		float SpawnRadius = 2000;//Redius in which spheres should spawn. Default 2000 in first wave

	void Wave();//Generates new wawe of spheres

	UPROPERTY(VisibleAnywhere, Category = SpawnLocation)// Array of pointers to spheres that are in radius 1500 around player 
		TArray<ASphereToSpawn*> SpheresInWave;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Waves)
		int WavesNum = 0;//waves counter

};
