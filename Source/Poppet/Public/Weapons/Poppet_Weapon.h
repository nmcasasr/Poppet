// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Poppet_Weapon.generated.h"

class ACharacter;

UCLASS()
class POPPET_API APoppet_Weapon : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APoppet_Weapon();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "Weapon")
	void BP_StartShooting();

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "Weapon")
	void BP_StopShooting();

	ACharacter* CurrentOwnerCharacter;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable)
	virtual void StartShooting();

	UFUNCTION(BlueprintCallable)
	virtual void StopShooting();


	UFUNCTION(BlueprintCallable)
	void setCharacterOwner(ACharacter* NewOwner);

};
