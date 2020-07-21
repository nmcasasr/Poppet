// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "Poppet_SaveGame.generated.h"

/**
 * 
 */
UCLASS()
class POPPET_API UPoppet_SaveGame : public USaveGame
{
	GENERATED_BODY()
	
protected:

	UPROPERTY(VisibleDefaultsOnly, Category = "Data")
	int PlayerDeathCounter;

public:

	UFUNCTION(BlueprintCallable)
	void SetPlayerDeathCounter(int NewValue) { PlayerDeathCounter = NewValue; };

	UFUNCTION(BlueprintCallable)
	int GetPlayerDeathCounter() { return PlayerDeathCounter; };
};
