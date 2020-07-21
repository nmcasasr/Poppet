// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Weapons/Poppet_Weapon.h"
#include "Poppet_Turret.generated.h"
class APoppet_Proyectile;
class APawn;
class APoppet_Character;
/**
 * 
 */
UENUM()
enum class EPoppet_TurretType : uint8 {
	TurretType_Jump		UMETA(DisplayName = "Jump Turret"),
	TurretType_Speed	UMETA(DisplayName = "Speed Turret"),
	TurretType_Damage	UMETA(DisplayName = "Damage Turret")
};
UCLASS()
class POPPET_API APoppet_Turret : public APoppet_Weapon
{
	GENERATED_BODY()

public:
	APoppet_Turret();
protected:

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Effects")
	FName MuzzleSocketName;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Weapon")
	TSubclassOf<APoppet_Proyectile> ProyectileClass;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Turret")
	EPoppet_TurretType TurretType;

protected:
	virtual void StartShooting() override;
	virtual void StopShooting() override;
};
