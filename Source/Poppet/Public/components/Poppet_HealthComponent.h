// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Poppet_HealthComponent.generated.h"
class UWorld;
DECLARE_DYNAMIC_MULTICAST_DELEGATE_SixParams(FOnHealthChangeSignature, UPoppet_HealthComponent*, HealthComponent, AActor *, DamagedActor, float, Damage, const UDamageType *, DamageType, AController *, InstigatedBy, AActor *, DamageCauser);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnHealthUpdateSignature, float, CurrentHealth, float, MaxHealth);
UCLASS( ClassGroup=(Poppet), meta=(BlueprintSpawnableComponent) )
class POPPET_API UPoppet_HealthComponent : public UActorComponent
{
	GENERATED_BODY()

protected:

	UPROPERTY(BlueprintReadOnly, Category = "Health Component")
	bool bIsDead;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "HealthComponent")
	float Health;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "HealthComponent", meta = (ClampMin = 0.0, UIMin = 0.0))
	float MaxHealth;

	UPROPERTY(BlueprintReadOnly, Category = "HealthComponent")
	AActor* MyOwner;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Movement")
	FTimerHandle dBurningTime;

	FTimerHandle TimerHandle_UpdateInitialHealth;
public:
	UPROPERTY(BlueprintAssignable)
	FOnHealthChangeSignature OnHealthChangeDelegate;

	UPROPERTY(BlueprintAssignable)
	FOnHealthUpdateSignature OnHealthUpdateDelegate;
public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Debug")
	bool bLogs;
public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Damage")
	float BurnDamageTime;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Damage")
	float InitialBurnDamageTime;
public:	
	// Sets default values for this component's properties
	UPoppet_HealthComponent();

	UFUNCTION(BlueprintCallable)
	bool IsDead() const { return bIsDead; };

	void UpdateInitialHealth();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UFUNCTION()
	void TakingDamage(AActor* DamagedActor, float Damage, const class UDamageType* DamageType, class AController* InstigatedBy, AActor* DamageCauser);

	void TakeBurnDamage();



public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
};
