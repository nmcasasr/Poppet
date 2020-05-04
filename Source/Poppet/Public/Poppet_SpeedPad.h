// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Poppet_SpeedPad.generated.h"
class UStaticMeshComponent;
class UCharacterMovementComponent;
class UBoxComponent;
class APoppet_Character;
UCLASS()

//Posible Actualizacion: Crear un super pad y heredar de el 
class POPPET_API APoppet_SpeedPad : public AActor
{
	GENERATED_BODY()

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
		UStaticMeshComponent* PadComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
		UBoxComponent* PlayerZoneColliderComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Launch Pad")
		FName PadTag;
public:	
	// Sets default values for this actor's properties
	APoppet_SpeedPad();

	UPROPERTY(VisibleAnywhere, Category = "Components")
		bool bCanLaunch;
	UPROPERTY(VisibleAnywhere, Category = "Components")
		float launchPower;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION()
		void CheckKeyFromPlayer(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);
	UFUNCTION()
		void StopPlayer(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);



public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void LaunchPlayer(APoppet_Character* OtherActor);
};
