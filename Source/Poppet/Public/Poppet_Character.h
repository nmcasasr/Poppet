// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "GameFramework/Actor.h"
#include "Poppet_Character.generated.h"

class UCameraComponent;
class USpringArmComponent;
class UWorld;
class APoppet_Weapon;

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
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
	TSubclassOf<APoppet_Weapon> InitialWeaponClass;

	UPROPERTY(BlueprintReadWrite, Category = "Weapon")
	APoppet_Weapon* CurrentWeapon;

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

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void AddItem(FName newItem);

	void DeleteItem();

	bool HasKey(FName itemTag);

	void setMeleeDetectorCollision(ECollisionEnabled::Type NewColissionState);

	UFUNCTION()
	void MakeMeleeAction(UPrimitiveComponent * OverlappedComponent, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);
};
