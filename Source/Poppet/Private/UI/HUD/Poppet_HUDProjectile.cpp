// Fill out your copyright notice in the Description page of Project Settings.


#include "Poppet_HUDProjectile.h"
#include "..\..\..\Public\UI\HUD\Poppet_HUDProjectile.h"
#include "Poppet_Character.h"
#include "Kismet/GameplayStatics.h"

void UPoppet_HUDProjectile::InitializeWidget()
{
	APawn* PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
	if (IsValid(PlayerPawn)) {

		APoppet_Character* PlayerCharacter = Cast<APoppet_Character>(PlayerPawn);
		if (IsValid(PlayerCharacter)) {
			PlayerCharacter->OnItemUpdateDelegate.AddDynamic(this, &UPoppet_HUDProjectile::UpdateItem);
			ActualColor = NoColor;
		}
	}
}

void UPoppet_HUDProjectile::UpdateItem(FName currentItem)
{
	if (currentItem == "KeyA"){
		ActualColor = GoldenColor;
	}
	else if (currentItem == "KeyB"){
		ActualColor = MetalColor;
	}
	else if (currentItem == "PowerUp") {
		ActualColor = PowerUpColor;
	}
	else {
		ActualColor = NoColor;
	}
}
