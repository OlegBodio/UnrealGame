// Fill out your copyright notice in the Description page of Project Settings.


#include "MyCharacter.h"
#include "SphereSpawner.h"
#include "SphereToSpawn.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "NewGameMode.h"


// Sets default values
AMyCharacter::AMyCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	GetCapsuleComponent()->InitCapsuleSize(40.f, 95.f);

	TurnRate = 45.0f;
	LookUpRate = 45.0f;

	FirstPersonCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("First Person Camera"));
	FirstPersonCamera->SetupAttachment(GetCapsuleComponent());
	FirstPersonCamera->AddRelativeLocation(FVector(-39.65f, 1.75f, 64.0f));
	FirstPersonCamera->bUsePawnControlRotation = true;

	HandsMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Character Mesh"));

	HandsMesh->SetOnlyOwnerSee(true);
	HandsMesh->SetupAttachment(FirstPersonCamera);
	HandsMesh->bCastDynamicShadow = true;
	HandsMesh->CastShadow = true;
	HandsMesh->AddRelativeRotation(FRotator(1.9f, -19.19f, 5.2f));
	HandsMesh->AddRelativeLocation(FVector(-0.5f, -4.4f, -155.7f));

	GunMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Gun"));
	GunMesh->SetOnlyOwnerSee(true);
	GunMesh->bCastDynamicShadow = true;
	GunMesh->CastShadow = true;

	MuzzleLocation = CreateDefaultSubobject<USceneComponent>(TEXT("Muzzle Location"));
	MuzzleLocation->SetupAttachment(GunMesh);
	MuzzleLocation->SetRelativeLocation(FVector(0.2f, 48.4f, -10.6f));

	GunOffSet = FVector(100.0f, 0.0f, 50.0f);

}

// Called when the game starts or when spawned
void AMyCharacter::BeginPlay()
{
	Super::BeginPlay();
	GunMesh->AttachToComponent(HandsMesh, FAttachmentTransformRules::SnapToTargetNotIncludingScale,
		TEXT("GripPoint"));//adds gun mesh to hands mesh

	World = GetWorld();
	AnimInstance = HandsMesh->GetAnimInstance();

}

// Called every frame
void AMyCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AMyCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)//Setting player controll
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);

	PlayerInputComponent->BindAction("Fire", IE_Pressed, this, &AMyCharacter::onFire);

	PlayerInputComponent->BindAxis("MoveForward", this, &AMyCharacter::moveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AMyCharacter::moveRight);

	PlayerInputComponent->BindAxis("Turn", this, &AMyCharacter::turnAtRate);
	PlayerInputComponent->BindAxis("LookUp", this, &AMyCharacter::lookAtRate);



}

void AMyCharacter::onFire()
{
	if (World != NULL)
	{
		SpawnRotation = GetControlRotation();
		SpawnLocation = ((MuzzleLocation != nullptr) ? MuzzleLocation->GetComponentLocation(): 
			GetActorLocation() + SpawnRotation.RotateVector(GunOffSet));
	/*
		if (MuzzleLocation != nullptr)
		{
			SpawnLocation = MuzzleLocation->GetComponentLocation();
		}
		else
		{
			SpawnLocation = GetActorLocation() + SpawnRotation.RotateVector(GunOffSet);
		}
	*/
	}
	FActorSpawnParameters ActorSpawnParams;
	ActorSpawnParams.SpawnCollisionHandlingOverride =
		ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButDontSpawnIfColliding;
    
	World->SpawnActor<ABullet>(Bullet, SpawnLocation, SpawnRotation, ActorSpawnParams);
	

}

void AMyCharacter::moveForward(float value)
{
	if (value != 0.0f)
	{
		AddMovementInput(GetActorForwardVector(), value);
	}
}

void AMyCharacter::moveRight(float value)
{
	if (value != 0.0f)
	{
		AddMovementInput(GetActorRightVector(), value);
	}
}

void AMyCharacter::turnAtRate(float rate)
{
	AddControllerYawInput(rate * TurnRate * GetWorld()->GetDeltaSeconds());
}

void AMyCharacter::lookAtRate(float rate)
{
	AddControllerPitchInput(rate * LookUpRate * GetWorld()->GetDeltaSeconds());
}



void AMyCharacter::TakeDamage(float Value)
{
	HP -= Value;//reduse HP

	if (HP <= 0.0f)// if HP is over
	{
		ANewGameMode* GameMode = Cast<ANewGameMode>(UGameplayStatics::GetGameMode(GetWorld()));//get Game mode
		if (GameMode)
		{
			GameMode->MyResetLevel();// Reset level
		}
	}
}

void AMyCharacter::AddDestroyedSphere()
{
	++SpheresDestoyedCount;
}

