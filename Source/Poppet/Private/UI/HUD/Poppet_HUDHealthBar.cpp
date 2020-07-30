// Fill out your copyright notice in the Description page of Project Settings.


#include "Poppet_HUDHealthBar.h"
#include "..\..\..\Public\UI\HUD\Poppet_HUDHealthBar.h"
#include "Poppet_Character.h"
#include "Kismet/GameplayStatics.h"
#include "components/Poppet_HealthComponent.h"

void UPoppet_HUDHealthBar::InitializeWidget()
{
	APawn* PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
	if (IsValid(PlayerPawn)) {

		APoppet_Character* PlayerCharacter = Cast<APoppet_Character>(PlayerPawn);
		if (IsValid(PlayerCharacter)) {
			UPoppet_HealthComponent* PlayerHealthcomponent = PlayerCharacter->GetHealthComponent();
			if (IsValid(PlayerHealthcomponent)) {
				PlayerHealthcomponent->OnHealthUpdateDelegate.AddDynamic(this, &UPoppet_HUDHealthBar::UpdateHealth);
			}
		}
	}
}

void UPoppet_HUDHealthBar::UpdateHealth(float CurrentHealth, float MaxHealth)
{
	HealthPercent = CurrentHealth / MaxHealth;
	UE_LOG(LogTemp, Log, TEXT("My health percentage is: %s"), *FString::SanitizeFloat(HealthPercent));
	HealthColor = FMath::Lerp(EmptyHealthColor, FullHealthColor, HealthPercent);

}
