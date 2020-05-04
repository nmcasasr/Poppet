// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Poppet_Proyectile.generated.h"
class UStaticMeshComponent;
class UProjectileMovementComponent;
class USphereComponent;
class APoppet_LaunchPad;
class APoppet_SpeedPad;
UCLASS()
class POPPET_API APoppet_Proyectile : public AActor
{
	GENERATED_BODY()
	
protected:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	USphereComponent* ProyectileCollision;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly,Category="Components")
	UStaticMeshComponent* ProyectileMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UProjectileMovementComponent* ProyectileMovementComponent;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Item")
	TSubclassOf<APoppet_LaunchPad> LaunchPadClass;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Item")
	TSubclassOf<APoppet_SpeedPad> SpeedPadClass;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Item")
	FName ObjectType;
public:	
	// Sets default values for this actor's properties
	APoppet_Proyectile();
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;

	virtual void SpawnObject(FName ObjectTyp);

};
