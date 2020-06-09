// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Items/Poppet_Item.h"
#include "Poppet_PowerUp.generated.h"

class UStaticMeshComponent;
/**
 * 
 */
UCLASS()
class POPPET_API APoppet_PowerUp : public APoppet_Item
{
	GENERATED_BODY()

protected:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UStaticMeshComponent* PowerUp_MeshComponent;
public:
	APoppet_PowerUp();

protected:
	virtual void Pickup(APoppet_Character* PickUpActor) override;
};
