// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Poppet_VictoryZone.generated.h"

class UBoxComponent;
class APoppet_GameMode;
UCLASS()
class POPPET_API APoppet_VictoryZone : public AActor
{
	GENERATED_BODY()

	
public:	
	// Sets default values for this actor's properties
	APoppet_VictoryZone();

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UBoxComponent* VictoryZoneComponent;

protected:

	APoppet_GameMode* GameModeReference;


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;	

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;

};
