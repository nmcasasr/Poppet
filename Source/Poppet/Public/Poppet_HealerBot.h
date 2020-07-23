// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Poppet_HealerBot.generated.h"

class UStaticMeshComponent;
class APoppet_Character;
class UParticleSystem;
class UParticleSystemComponent;
UCLASS()
class POPPET_API APoppet_HealerBot : public APawn
{
	GENERATED_BODY()

public:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
		UStaticMeshComponent* MainMeshComponent;

protected:

	UPROPERTY(BlueprintReadOnly, Category = "Healer Bot")
	FVector NextPathPoint;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Heal Distance")
	float MinDistanceToPlayer;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Movement")
	float ForceMagnitude;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Movement")
	float ParticleDistance;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Movement")
	FName Item;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Movement")
	FName SocketName;

	UPROPERTY(BlueprintReadOnly, Category = "Reference")
	APoppet_Character* PlayerCharacter;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Effects")
	UParticleSystem* TraceEffect;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Effects")
	FName TraceParamName;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Effects")
	FName TraceParamNameSource;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Effects")
	UParticleSystemComponent* TracerComponent;
public:
	// Sets default values for this pawn's properties
	APoppet_HealerBot();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable, Category = "Navigation")
		FVector GetNextPathPoint();

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
