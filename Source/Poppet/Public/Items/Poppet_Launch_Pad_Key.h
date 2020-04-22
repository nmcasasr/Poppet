// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Items/Poppet_Item.h"
#include "Poppet_Launch_Pad_Key.generated.h"


class UStaticMeshComponent;
/**
 * 
 */
UCLASS()
class POPPET_API APoppet_Launch_Pad_Key : public APoppet_Item
{
	GENERATED_BODY()
	

protected:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UStaticMeshComponent* Launch_Pad_KeyMeshComponent;

protected:

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Key")
	FName KeyTag;

public:

	APoppet_Launch_Pad_Key();
		
public:

	UFUNCTION(BlueprintCallable, Category = "Getter")
	FName GetKeyTag() const { return KeyTag; };

protected:
	virtual void Pickup(APoppet_Character* PickUpActor) override;
};
