// Fill out your copyright notice in the Description page of Project Settings.


#include "Poppet_Proyectile.h"
#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "..\..\Public\Weapons\Poppet_Proyectile.h"
#include "Poppet_LaunchPad.h"
#include "Poppet_SpeedPad.h"

// Sets default values
APoppet_Proyectile::APoppet_Proyectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	ProyectileCollision = CreateDefaultSubobject<USphereComponent>(TEXT("ProyectileCollision"));
	RootComponent = ProyectileCollision;

	ProyectileMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ProyectileStaticMesh"));
	ProyectileMesh->SetupAttachment(RootComponent);

	ProyectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProyectileMovement"));
	ProyectileMovementComponent->InitialSpeed = 3000;
	ProyectileMovementComponent->MaxSpeed = 3000;
	ObjectType = "KeyA";



}

// Called when the game starts or when spawned
void APoppet_Proyectile::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APoppet_Proyectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void APoppet_Proyectile::NotifyActorBeginOverlap(AActor * OtherActor)
{
	if (OtherActor && (OtherActor != this))
	{
		Super::NotifyActorBeginOverlap(OtherActor);
		FVector Location = GetActorLocation();
		FRotator rotation = GetActorRotation();

		if (OtherActor->ActorHasTag(TEXT("Wall"))) {
			FRotator rotation2 = OtherActor->GetActorRotation();
			if (ObjectType == "KeyA") {
			
			APoppet_LaunchPad* CurrentProyectile = GetWorld()->SpawnActor<APoppet_LaunchPad>(LaunchPadClass, FVector(Location.X, Location.Y, Location.Z), FRotator(90, rotation.Yaw, rotation2.Roll));
			CurrentProyectile->launchPower = 2000;
			}
		}
		else if (OtherActor->ActorHasTag(TEXT("Floor")))
		{
			if (ObjectType == "KeyA")
			{
			APoppet_LaunchPad* CurrentProyectile = GetWorld()->SpawnActor<APoppet_LaunchPad>(LaunchPadClass,FVector(Location.X, Location.Y, Location.Z), FRotator::ZeroRotator);
			}
			else {
			APoppet_SpeedPad* CurrentProyectile = GetWorld()->SpawnActor<APoppet_SpeedPad>(SpeedPadClass, FVector(Location.X, Location.Y, Location.Z), FRotator(0,rotation.Yaw,0));
			}
		
		}		
		Destroy();
	}

}

void APoppet_Proyectile::SpawnObject(FName spawnObject)
{
	ObjectType = spawnObject;
}

