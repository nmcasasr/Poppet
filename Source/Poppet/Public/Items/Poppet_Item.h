// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Poppet_Item.generated.h"

class USphereComponent;
class APoppet_Character;
class USoundCue;

UCLASS()
class POPPET_API APoppet_Item : public AActor
{
	GENERATED_BODY()

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	USphereComponent* MainColliderComponent;
	
public:	
	// Sets default values for this actor's properties
	APoppet_Item();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void Pickup(APoppet_Character* PickUpActor);

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category="Item")
	void BP_Pickup(APoppet_Character* PickupActor);

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Audio")
	USoundCue* PickUpSound;
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;

	UFUNCTION(BlueprintCallable)
	void PlaySound(USoundCue* SoundCue, bool bIs3D = false, FVector SoundLocation = FVector::ZeroVector);
};
