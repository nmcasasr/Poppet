// Fill out your copyright notice in the Description page of Project Settings.


#include "Poppet_HealthComponent.h"
#include "Core/Poppet_BarrelDamage.h"
#include "..\..\Public\components\Poppet_HealthComponent.h"
#include <GameFramework/Actor.h>

// Sets default values for this component's properties
UPoppet_HealthComponent::UPoppet_HealthComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	MaxHealth = 100.0f;
	bIsDead = false;
	bLogs = true;
	InitialBurnDamageTime = 5.0f;
}


void UPoppet_HealthComponent::UpdateInitialHealth()
{
	OnHealthUpdateDelegate.Broadcast(Health, MaxHealth);
}

// Called when the game starts
void UPoppet_HealthComponent::BeginPlay()
{
	Super::BeginPlay();

	Health = MaxHealth;
	BurnDamageTime = InitialBurnDamageTime;
	MyOwner = GetOwner();
	if (IsValid(MyOwner)) {
	MyOwner->OnTakeAnyDamage.AddDynamic(this, &UPoppet_HealthComponent::TakingDamage);
	}
	GetWorld()->GetTimerManager().SetTimer(TimerHandle_UpdateInitialHealth, this, &UPoppet_HealthComponent::UpdateInitialHealth, 0.2f, false);
	
}

void UPoppet_HealthComponent::TakingDamage(AActor * DamagedActor, float Damage, const UDamageType * DamageType, AController * InstigatedBy, AActor * DamageCauser)
{
	const UPoppet_BarrelDamage* BarrelDamage = Cast<UPoppet_BarrelDamage>(DamageType);
	if (Damage <= 0.0f || bIsDead) {
		return;
	}
	if (IsValid(BarrelDamage)) {
		GetWorld()->GetTimerManager().SetTimer(dBurningTime, this, &UPoppet_HealthComponent::TakeBurnDamage, 1.0f, true);
	}
	
	Health = FMath::Clamp(Health - Damage, 0.0f, MaxHealth);
	
	if (Health == 0.0f) {
		UE_LOG(LogTemp, Warning, TEXT("Is Dead"));
		bIsDead = true;
	}
	OnHealthChangeDelegate.Broadcast(this, DamagedActor, Damage, DamageType, InstigatedBy, DamageCauser);
	OnHealthUpdateDelegate.Broadcast(Health, MaxHealth);
	if (bLogs) {
		UE_LOG(LogTemp, Log, TEXT("My health is: %s"), *FString::SanitizeFloat(Health));
	}
	//
}

void UPoppet_HealthComponent::TakeBurnDamage()
{
	Health = FMath::Clamp(Health - 20.0f, 0.0f, MaxHealth);
	if (Health == 0.0f) {
		UE_LOG(LogTemp, Warning, TEXT("Is Dead"));
		bIsDead = true;
	}
	if (--BurnDamageTime <= 0) {
		GetWorld()->GetTimerManager().ClearTimer(dBurningTime);
		BurnDamageTime = InitialBurnDamageTime;
	}
	OnHealthUpdateDelegate.Broadcast(Health, MaxHealth);
}


// Called every frame
void UPoppet_HealthComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

