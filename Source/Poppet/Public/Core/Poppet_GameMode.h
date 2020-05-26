// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "Poppet_GameMode.generated.h"

/**
 * 
 */
class APoppet_Character;
class APoppet_SpectatingCamera;

UCLASS()
class POPPET_API APoppet_GameMode : public AGameModeBase
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Spectating Camera")
	float SpectatingBlendTime;

	UPROPERTY(BlueprintReadOnly, Category = "Spectating Camera")
		APoppet_SpectatingCamera* VictoryCamera;

	UPROPERTY(BlueprintReadOnly, Category = "Spectating Camera")
		APoppet_SpectatingCamera* GameOverCamera;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Movement")
	FTimerHandle dRestartCoolDown;
	
public:
	UFUNCTION()
	void Victory(APoppet_Character* Character);

	UFUNCTION()
	void GameOver(APoppet_Character* Character);

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void BP_GameOver();

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void BP_Victory();
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void SetupSpectatingCameras();

	void MoveCameraToSpectatingPoint(APoppet_Character* Character,APoppet_SpectatingCamera* SpectatingCamera);

	void RestartLevel();

};
