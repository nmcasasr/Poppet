// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/StaticMeshComponent.h"
#include "Poppet_ItemSpawner.generated.h"

class UStaticMeshComponent;
class APoppet_HealerBot;
class USoundCue;
UCLASS()
class POPPET_API APoppet_ItemSpawner : public AActor
{
	GENERATED_BODY()

public:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UStaticMeshComponent* MainMeshComponent;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Spawner")
	TSubclassOf<APoppet_HealerBot> ItemClass;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Spawner")
	FVector SpawnPoint;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Audio")
	USoundCue* SpawnSound;
protected:

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Spawner")
	bool bIsActive;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Spawner", meta = (UIMin = 1.0, ClampMin = 1.0))
	int MaxBotsCounter;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Spawner", meta = (UIMin = 0.1, ClampMin = 0.1))
	float TimeToSpawn;

	UPROPERTY(BlueprintReadOnly, Category = "Spawner")
	int CurrentBotsCounter;

	FTimerHandle TimerHandle_Spawn;

public:	
	// Sets default values for this actor's properties
	APoppet_ItemSpawner();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void SpawnItem();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void DeleteItem() { CurrentBotsCounter--; };

	void SetActive(bool ActiveState) { bIsActive = ActiveState; };

	void PlaySound();

};
