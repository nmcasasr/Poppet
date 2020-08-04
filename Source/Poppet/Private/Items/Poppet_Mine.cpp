// Fill out your copyright notice in the Description page of Project Settings.


#include "Poppet_Mine.h"
#include "..\..\Public\Items\Poppet_Mine.h"
#include "Components/Poppet_HealthComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Components/SphereComponent.h"
#include "Sound/SoundCue.h"
#include "Poppet_Character.h"
#include "Engine.h"
#include <GameFramework/Actor.h>
#include "Particles/ParticleSystem.h"

// Sets default values
APoppet_Mine::APoppet_Mine()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	InitialPosition = GetActorLocation();

	HealthComponent = CreateDefaultSubobject<UPoppet_HealthComponent>(TEXT("HealthComponent"));
	MineComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mine"));
	MainColliderComponent = CreateDefaultSubobject<USphereComponent>(TEXT("MainColliderComponent"));
	RootComponent = MineComponent;
	MainColliderComponent->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void APoppet_Mine::BeginPlay()
{
	Super::BeginPlay();
	HealthComponent->OnHealthChangeDelegate.AddDynamic(this, &APoppet_Mine::OnHealthChange);
}

void APoppet_Mine::OnHealthChange(UPoppet_HealthComponent * MyHealthComponent, AActor * DamagedActor, float Damage, const UDamageType * DamageType, AController * InstigatedBy, AActor * DamageCauser)
{
	UE_LOG(LogTemp, Warning, TEXT("Mine change"));
	if (HealthComponent->IsDead()) {
		AController* controler = this->GetInstigatorController();
		TArray<AActor*> ignoredActors;
		UGameplayStatics::ApplyRadialDamage(GetWorld(), 100.0f, InitialPosition, 2000.0f, MyDamageType, ignoredActors, this, controler);
		if (IsValid(ExplosionEffect)) {
			UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), ExplosionEffect, GetActorLocation());
		}
		Destroy();
	}
}

// Called every frame
void APoppet_Mine::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void APoppet_Mine::NotifyActorBeginOverlap(AActor * OtherActor)
{
	Super::NotifyActorBeginOverlap(OtherActor);

	if (IsValid(OtherActor)) {
		APoppet_Character* CharacterComponent = Cast<APoppet_Character>(OtherActor);
		FTimerDelegate TimerDel;
		if (IsValid(CharacterComponent)) {
			TimerDel.BindUFunction(this, FName("ActorDistance"), CharacterComponent);
			GetWorld()->GetTimerManager().SetTimer(dActorTimer, TimerDel, 0.1f, true);
		}
	}

}

void APoppet_Mine::NotifyActorEndOverlap(AActor * OtherActor)
{
	GetWorld()->GetTimerManager().ClearTimer(dActorTimer);
	SetActorLocation(FVector(GetActorLocation().X, GetActorLocation().Y, InitialPosition.Z-50));
}

void APoppet_Mine::ActorDistance(APoppet_Character* OtherActor)
{
	float distance = FVector::Dist(GetActorLocation(), OtherActor->GetActorLocation());
	UE_LOG(LogTemp, Log, TEXT("Distance: %s"), *FString::SanitizeFloat(distance));
	FVector Location = GetActorLocation();
	SetActorLocation(Location+(FVector(0,0,distance/1200)));
	if (distance < 135) {
		AController* controler = this->GetInstigatorController();
		TArray<AActor*> ignoredActors;
		UGameplayStatics::ApplyRadialDamage(GetWorld(), 100.0f, OtherActor->GetActorLocation(), 200.0f, MyDamageType, ignoredActors, this, controler);
		if (IsValid(ExplosionEffect)) {
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), ExplosionEffect, InitialPosition);
		}
		PlaySound(ExplosionSound, true, GetActorLocation());
		Destroy();
	}
}

void APoppet_Mine::PlaySound(USoundCue * SoundCue, bool bIs3D, FVector SoundLocation)
{
	if (!IsValid(SoundCue))
	{
		return;
	}
	if (bIs3D)
	{
		UGameplayStatics::PlaySoundAtLocation(GetWorld(), SoundCue, SoundLocation);
	}
	else {
		UGameplayStatics::PlaySound2D(GetWorld(), SoundCue);
	}
}
