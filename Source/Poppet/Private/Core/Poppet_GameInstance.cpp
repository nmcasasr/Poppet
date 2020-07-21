// Fill out your copyright notice in the Description page of Project Settings.


#include "Poppet_GameInstance.h"
#include "Kismet/GameplayStatics.h"
#include "SaveSystem/Poppet_SaveGame.h"


UPoppet_GameInstance::UPoppet_GameInstance() {

	SaveSlotName = "Poppet_SaveData";
}

void UPoppet_GameInstance::AddPlayerDeathToCounter()
{
	
	PlayerDeathCounter++;
	BP_AddPlayerDeathToCounter();
}

void UPoppet_GameInstance::SaveData()
{
	USaveGame* SaveGameObject = nullptr;
	bool bExistingData = UGameplayStatics::DoesSaveGameExist(SaveSlotName, 0);
	if (bExistingData) {
		SaveGameObject = UGameplayStatics::LoadGameFromSlot(SaveSlotName, 0);
	}
	else {
		SaveGameObject = UGameplayStatics::CreateSaveGameObject(UPoppet_SaveGame::StaticClass());
	}
	if (IsValid(SaveGameObject))
	{
		UPoppet_SaveGame* SaveFile = Cast<UPoppet_SaveGame>(SaveGameObject);
		if (IsValid(SaveFile)) {
			SaveFile->SetPlayerDeathCounter(PlayerDeathCounter);

			UGameplayStatics::SaveGameToSlot(SaveFile, SaveSlotName, 0);
		}
	}
	BP_SaveData();
}

void UPoppet_GameInstance::LoadData()
{
	USaveGame* SaveGameObject = nullptr;
	bool bExistingData = UGameplayStatics::DoesSaveGameExist(SaveSlotName, 0);
	if (bExistingData) {
		SaveGameObject = UGameplayStatics::LoadGameFromSlot(SaveSlotName, 0);
	}
	if (IsValid(SaveGameObject))
	{
		UPoppet_SaveGame* SaveFile = Cast<UPoppet_SaveGame>(SaveGameObject);
		if (IsValid(SaveFile)) {
			PlayerDeathCounter = SaveFile->GetPlayerDeathCounter();
		}
	}
	BP_LoadData();
}

void UPoppet_GameInstance::ResetData()
{
	PlayerDeathCounter = 0;
	BP_ResetData();
}
