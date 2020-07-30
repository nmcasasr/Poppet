// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Poppet_HUDHealthBar.generated.h"

/**
 * 
 */
UCLASS()
class POPPET_API UPoppet_HUDHealthBar : public UUserWidget
{
	GENERATED_BODY()

protected:

	UPROPERTY(BlueprintReadOnly, Category = "Setup")
	float HealthPercent;

	UPROPERTY(BlueprintReadOnly, Category = "Setup")
	FLinearColor HealthColor;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Setup")
	FLinearColor FullHealthColor;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Setup")
	FLinearColor EmptyHealthColor;

public:

	UFUNCTION(BlueprintCallable)
	void InitializeWidget();

	UFUNCTION()
	void UpdateHealth(float CurrentHealth, float MaxHealth);


	
};
