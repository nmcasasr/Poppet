// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Poppet_HealerBot.generated.h"

class UStaticMeshComponent;
class APoppet_Character;
class UParticleSystem;
class UParticleSystemComponent;
class APoppet_ItemSpawner;
class UAudioComponent;
class USoundCue;

UCLASS()
class POPPET_API APoppet_HealerBot : public APawn
{
	GENERATED_BODY()

public:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UStaticMeshComponent* MainMeshComponent;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Audio")
	USoundCue* ConnectionSound;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Audio")
	USoundCue* LoseConnectionSound;

protected:

	UPROPERTY(BlueprintReadOnly, Category = "Healer Bot")
	FVector NextPathPoint;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Heal Distance")
	float MinDistanceToPlayer;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Movement")
	float ForceMagnitude;


	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Movement")
	float maxPlayerDistance;

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

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Time", meta = (UIMin = 0.1, ClampMin = 0.1))
	float LifeTime;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Time", meta = (UIMin = 0.1, ClampMin = 0.1))
	float InitLifeTime;

	UPROPERTY(BlueprintReadOnly, Category = "Spawner")
	APoppet_ItemSpawner* MySpawner;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UAudioComponent* ConnectionSoundComponent;

	FTimerHandle TimerHandle_Spawn;

	bool bIsInRange;

	bool bIsPlaying;
public:
	// Sets default values for this pawn's properties
	APoppet_HealerBot();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable, Category = "Navigation")
	FVector GetNextPathPoint();

	void DestroyItem();

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void SetSpawner(APoppet_ItemSpawner* Spawner) { MySpawner = Spawner; };

	void PlaySound(USoundCue* VoiceSound);

	void StopSound();

};
