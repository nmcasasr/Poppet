// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Poppet_LevelMusic.generated.h"

class UAudioComponent;
class UBillboardComponent;
class APoppet_GameMode;

UCLASS()
class POPPET_API APoppet_LevelMusic : public AActor
{
	GENERATED_BODY()

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UBillboardComponent* MusicBillBoardComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UAudioComponent* MusicAudioComponent;

protected:

	UPROPERTY(BlueprintReadOnly, Category = "References")
	APoppet_GameMode* GameMmodeReference;
	
public:	
	// Sets default values for this actor's properties
	APoppet_LevelMusic();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION()
	void StopLevelMusic();

};
