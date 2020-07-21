// Fill out your copyright notice in the Description page of Project Settings.


#include "Poppet_MainMenuWidget.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"
#include "GameFramework/PlayerController.h"
#include "Core/Poppet_GameInstance.h"


void UPoppet_MainMenuWidget::NewGame()
{
	BP_NewGame();

	UPoppet_GameInstance* GameInstanceReference = Cast<UPoppet_GameInstance>(GetWorld()->GetGameInstance());
	if (IsValid(GameInstanceReference)) {
		GameInstanceReference->ResetData();
	}

	UGameplayStatics::OpenLevel(GetWorld(), GameplayLevelName);
}

void UPoppet_MainMenuWidget::ContinueGame()
{

	UPoppet_GameInstance* GameInstanceReference = Cast<UPoppet_GameInstance>(GetWorld()->GetGameInstance());
	if (IsValid(GameInstanceReference)) {
		GameInstanceReference->LoadData();
	}
	BP_ContinueGame();
	UGameplayStatics::OpenLevel(GetWorld(), GameplayLevelName);
}

void UPoppet_MainMenuWidget::ExitGame()
{

	BP_ExitGame();
	APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	UKismetSystemLibrary::QuitGame(GetWorld(), PlayerController, EQuitPreference::Quit, false);
}
