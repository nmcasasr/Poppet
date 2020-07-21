// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "Poppet_GameInstance.generated.h"

/**
 * 
 */
UCLASS()
class POPPET_API UPoppet_GameInstance : public UGameInstance
{
	GENERATED_BODY()

public:

	UPoppet_GameInstance();

protected:

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Save System")
	FString SaveSlotName;

	UPROPERTY(VisibleAnywhere, Category = "Player Data")
	int PlayerDeathCounter;

public:

	UFUNCTION(BlueprintCallable)
	int GetPlayerDeathCounter() { return PlayerDeathCounter; };

	UFUNCTION(BlueprintCallable)
	void SetPlayerDeathCounter(int NewValue) { PlayerDeathCounter = NewValue; }

	UFUNCTION(BlueprintCallable)
	void AddPlayerDeathToCounter();

	UFUNCTION(BlueprintCallable)
	void SaveData();

	UFUNCTION(BlueprintCallable)
	void LoadData();

	UFUNCTION(BlueprintCallable)
	void ResetData();

protected:

	UFUNCTION(BlueprintImplementableEvent)
	void BP_AddPlayerDeathToCounter();
	
	UFUNCTION(BlueprintImplementableEvent)
	void BP_SaveData();

	UFUNCTION(BlueprintImplementableEvent)
	void BP_LoadData();

	UFUNCTION(BlueprintImplementableEvent)
	void BP_ResetData();
};
