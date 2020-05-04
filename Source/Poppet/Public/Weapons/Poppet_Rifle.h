// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Weapons/Poppet_Weapon.h"
#include "Poppet_Rifle.generated.h"

class APoppet_Proyectile;
class APawn;
class APoppet_Character;
/**
 * 
 */
UCLASS()
class POPPET_API APoppet_Rifle : public APoppet_Weapon
{
	GENERATED_BODY()

public:

		APoppet_Rifle();

protected:
	
	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly,Category = "Effects")
	FName MuzzleSocketName;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Weapon")
	TSubclassOf<APoppet_Proyectile> ProyectileClass;

protected:
	virtual void StartShooting() override;
	virtual void StopShooting() override;
	
};
