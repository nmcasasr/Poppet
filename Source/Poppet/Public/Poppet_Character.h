// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "GameFramework/Actor.h"
#include "GameFramework/CheatManager.h"
#include "Poppet_Character.generated.h"

class UCameraComponent;
class USpringArmComponent;
class UWorld;
class UCheatManager;
class APoppet_Weapon;
class APoppet_GameMode;
class UPoppet_HealthComponent;
class UParticleSystem;
class UAnimInstance;
class UAnimMontage;
class UPoppet_GameInstance;

UCLASS()
class POPPET_API APoppet_Character : public ACharacter
{
	GENERATED_BODY()

protected:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UCameraComponent* FPSCameraComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UCameraComponent* TPSCameraComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	USpringArmComponent* SpringArmComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UCapsuleComponent* MeleeDetectorComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UPoppet_HealthComponent* HealthComponent;

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Camera")
	bool bUserFirstPersonView;

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Movement")
	bool bIsDashing;
	bool bCanDash;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Movement")
	bool bIsKicking;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Movement")
	FTimerHandle dDashingCoolDown;
protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Melee")
	FName MeleeSocketName;
protected:
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category	= "Items")
	FName Items;
protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Damage")
	float InitialBurnTime;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Damage")
	float BurnTime;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Movement")
	FTimerHandle dBurnCoolDown;
protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
	TSubclassOf<APoppet_Weapon> InitialWeaponClass;

	UPROPERTY(BlueprintReadWrite, Category = "Weapon")
	APoppet_Weapon* CurrentWeapon;

	APoppet_GameMode* GameModeReference;

	UPoppet_GameInstance* GameInstanceReference;
protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Effects")
	UParticleSystem* BurnEffect;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Effects")
	FName BurnSocketName;
public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "PowerUp")
	bool bCanUsePowerUp;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "PowerUp")
	bool bIsUsingPowerUp;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "PowerUp|Time", meta = (ClampMin = 0.0, UIMin = 0.0))
	float MaxPowerUpDuration;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "PowerUp|Time")
	float CurrentPowerUpDuration;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "PowerUp|Time", meta = (ClampMin = 0.0, UIMin = 0.0))
	float PowerUpPlayRate;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "PowerUp|Time")
	float PlayRate;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Animation")
	UAnimMontage* PowerUpMontage;

	UAnimInstance* MyAnimInstance;

	FTimerHandle TimerHandle_BeginPowerUp;
public:
	// Sets default values for this character's properties
	APoppet_Character();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void CreateInitalWeapon();

	void MoveForward(float value);
	void MoveRight(float value);
	virtual void Jump() override;
	virtual void StopJumping() override;
	void CrouchCharacter();
	void Dash();
	void restartDash();

	void RestartLevel();

	void StartShooting();
	void StopShooting();

	void StartMeele();
	void StopMeele();

	void CheckDamage();

	void GoToMainMenu();


	UFUNCTION()
		void OnHealthChange(UPoppet_HealthComponent* MyHealthComponent, AActor * DamagedActor, float Damage, const UDamageType * DamageType, AController * InstigatedBy, AActor * DamageCauser);
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void AddItem(FName newItem);

	void DeleteItem();

	bool HasKey(FName itemTag);

	void setMeleeDetectorCollision(ECollisionEnabled::Type NewColissionState);

	void StartBurning();

	UFUNCTION()
	void MakeMeleeAction(UPrimitiveComponent * OverlappedComponent, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);

	UFUNCTION(BlueprintCallable)
	void GainPowerUp();
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void BP_StartPowerUp();
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void BP_StopPowerUp();

	void UpdatePowerUpDuration(float Value);

	void BeginPowerUp();
};
