// Fill out your copyright notice in the Description page of Project Settings.


#include "Poppet_Barrel.h"
#include "Components/Poppet_HealthComponent.h"
#include "..\..\Public\Items\Poppet_Barrel.h"
#include "Kismet/GameplayStatics.h"
#include "Particles/ParticleSystem.h"

// Sets default values
APoppet_Barrel::APoppet_Barrel()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	HealthComponent = CreateDefaultSubobject<UPoppet_HealthComponent>(TEXT("HealthComponent"));
	BarrelComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Barrel"));
	RootComponent = BarrelComponent;
}

// Called when the game starts or when spawned
void APoppet_Barrel::BeginPlay()
{
	Super::BeginPlay();
	HealthComponent->OnHealthChangeDelegate.AddDynamic(this, &APoppet_Barrel::OnHealthChange);
	
}

void APoppet_Barrel::OnHealthChange(UPoppet_HealthComponent * MyHealthComponent, AActor * DamagedActor, float Damage, const UDamageType * DamageType, AController * InstigatedBy, AActor * DamageCauser)
{
	UE_LOG(LogTemp, Warning, TEXT("Barrel change"));
	if (HealthComponent->IsDead()) {
		AController* controler = this->GetInstigatorController();
		TArray<AActor*> ignoredActors;
		UGameplayStatics::ApplyRadialDamage(GetWorld(), 50.0f, GetActorLocation(), 100.0f, MyDamageType, ignoredActors, this, controler);
		if (IsValid(ExplosionEffect)) {
			UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), ExplosionEffect, GetActorLocation());
		}
		Destroy();
	}
}

// Called every frame
void APoppet_Barrel::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

