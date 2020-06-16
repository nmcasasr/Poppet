// Fill out your copyright notice in the Description page of Project Settings.


#include "Poppet_Enemy.h"
#include "Components/Poppet_HealthComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Components/SphereComponent.h"
#include "Poppet_Character.h"
#include "Engine.h"
#include <GameFramework/Actor.h>
#include "Particles/ParticleSystem.h"
// Sets default values
APoppet_Enemy::APoppet_Enemy()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	InitialPosition = GetActorLocation();

	HealthComponent = CreateDefaultSubobject<UPoppet_HealthComponent>(TEXT("HealthComponent"));
	MineComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mine"));
	MainColliderComponent = CreateDefaultSubobject<USphereComponent>(TEXT("MainColliderComponent"));
	RootComponent = MineComponent;
	MainColliderComponent->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void APoppet_Enemy::BeginPlay()
{
	Super::BeginPlay();
	HealthComponent->OnHealthChangeDelegate.AddDynamic(this, &APoppet_Enemy::OnHealthChange);
}

void APoppet_Enemy::OnHealthChange(UPoppet_HealthComponent * MyHealthComponent, AActor * DamagedActor, float Damage, const UDamageType * DamageType, AController * InstigatedBy, AActor * DamageCauser)
{
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
void APoppet_Enemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void APoppet_Enemy::NotifyActorBeginOverlap(AActor * OtherActor)
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

void APoppet_Enemy::NotifyActorEndOverlap(AActor * OtherActor)
{
	GetWorld()->GetTimerManager().ClearTimer(dActorTimer);
	SetActorLocation(FVector(GetActorLocation().X, GetActorLocation().Y, InitialPosition.Z));
}

void APoppet_Enemy::ActorDistance(APoppet_Character * OtherActor)
{
	float distance = FVector::Dist(GetActorLocation(), OtherActor->GetActorLocation());
	//UE_LOG(LogTemp, Log, TEXT("Distance: %s"), *FString::SanitizeFloat(distance));
	float OldRange = (174 - 134);
	float NewValue = 0;
	float NewRange = 0;
	if (OldRange == 0)
	{
		NewValue = 0;
	}	
	else
	{
	NewRange = (50 - 0);
	NewValue = (((distance - 134) * NewRange) / OldRange) + 0;
	}
	FVector Location = GetActorLocation();
	SetActorLocation(Location + (FVector(0, 0, NewValue)));
	UE_LOG(LogTemp, Log, TEXT("Distance: %s"), *FString::SanitizeFloat(NewValue));
	if (NewValue < 5) {
		AController* controler = this->GetInstigatorController();
		TArray<AActor*> ignoredActors;
		UGameplayStatics::ApplyRadialDamage(GetWorld(), 100.0f, OtherActor->GetActorLocation(), 200.0f, MyDamageType, ignoredActors, this, controler);
		if (IsValid(ExplosionEffect)) {
			UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), ExplosionEffect, InitialPosition);
		}
		Destroy();
	}
}

// Called to bind functionality to input
void APoppet_Enemy::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

