// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GameFramework/Character.h"
#include "Poppet_Mine.generated.h"

class UPoppet_HealthComponent;
class UDamageType;
class USphereComponent;
class UWorld;
class APoppet_Character;
class UParticleSystem;

UCLASS()
class POPPET_API APoppet_Mine : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APoppet_Mine();
protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UPoppet_HealthComponent* HealthComponent;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UStaticMeshComponent* MineComponent;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	USphereComponent* MainColliderComponent;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Weapon")
	TSubclassOf<UDamageType> MyDamageType;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Movement")
	FTimerHandle dActorTimer;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Movement")
	FTimerHandle dDashingCoolDown;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Movement")
	FVector InitialPosition;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION()
	void OnHealthChange(UPoppet_HealthComponent* MyHealthComponent, AActor * DamagedActor, float Damage, const UDamageType * DamageType, AController * InstigatedBy, AActor * DamageCauser);
protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Effects")
	UParticleSystem* ExplosionEffect;
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;
	virtual void NotifyActorEndOverlap(AActor* OtherActor) override;

	UFUNCTION()
	void ActorDistance(APoppet_Character* PickupActor);

};
