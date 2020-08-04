// Fill out your copyright notice in the Description page of Project Settings.


#include "Poppet_GameMode.h"
#include "Poppet_Character.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/PawnMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Poppet_SpectatingCamera.h"
#include "Sound/SoundCue.h"
#include "..\..\Public\Core\Poppet_GameMode.h"
#include <GameFramework/Actor.h>


void APoppet_GameMode::BeginPlay()
{
	Super::BeginPlay();
	SetupSpectatingCameras();
}
void APoppet_GameMode::GameOver(APoppet_Character* Character)
{
	OnGameOverDelegate.Broadcast();
	Character->GetMovementComponent()->StopMovementImmediately();
	Character->GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	//Character->DetachFromControllerPendingDestroy();

	//Character->SetLifeSpan(4.0f);
	Character->DisableInput(nullptr);
	PlaySound(GameOverSound);
	MoveCameraToSpectatingPoint(Character, GameOverCamera);
	GetWorld()->GetTimerManager().SetTimer(dRestartCoolDown, this, &APoppet_GameMode::RestartLevel, 3.0f, false);
}
void APoppet_GameMode::Victory(APoppet_Character* Character)
{
	OnVictoryeDelegate.Broadcast();
	Character->DisableInput(nullptr);
	PlaySound(VictorySound);
	MoveCameraToSpectatingPoint(Character, VictoryCamera);
	GetWorld()->GetTimerManager().SetTimer(dRestartCoolDown, this, &APoppet_GameMode::goToMenu, 3.0f, false);
}
void APoppet_GameMode::SetupSpectatingCameras()
{
	TArray<AActor*> SpectatingCameraActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), APoppet_SpectatingCamera::StaticClass(), SpectatingCameraActors);

	if (SpectatingCameraActors.Num() > 0) {
		for (AActor* SpectatingActor : SpectatingCameraActors) {
			APoppet_SpectatingCamera* SpectatingCamera = Cast<APoppet_SpectatingCamera>(SpectatingActor);
			if (IsValid(SpectatingCamera)) {
				switch (SpectatingCamera->GetCameraType())
				{
				case EPoppet_SpectatingCameraType::CameraType_Victory:
					VictoryCamera = SpectatingCamera;
					break;
				case EPoppet_SpectatingCameraType::CameraType_GameOver:
					GameOverCamera = SpectatingCamera;
					break;
				default:
					break;
				}
			}
		}
	}

}

void APoppet_GameMode::MoveCameraToSpectatingPoint(APoppet_Character* Character,APoppet_SpectatingCamera * SpectatingCamera)
{
	AController* CharacterController = Character->GetController();
	if (IsValid(CharacterController) && IsValid(Character)  && IsValid(SpectatingCamera)) {
		APlayerController* PlayerController = Cast<APlayerController>(CharacterController);
		if (IsValid(PlayerController)) {
			PlayerController->SetViewTargetWithBlend(SpectatingCamera, SpectatingBlendTime, EViewTargetBlendFunction::VTBlend_Cubic);
		}
	}
}

void APoppet_GameMode::RestartLevel()
{
	GetWorldTimerManager().ClearTimer(dRestartCoolDown);
	UGameplayStatics::OpenLevel(this, FName(*GetWorld()->GetName()), false);
}

void APoppet_GameMode::goToMenu()
{
	GetWorldTimerManager().ClearTimer(dRestartCoolDown);
	UGameplayStatics::OpenLevel(GetWorld(), FName("Menu"));
}

void APoppet_GameMode::PlaySound(USoundCue * SoundCue)
{
	if (!IsValid(SoundCue))
	{
		return;
	}
	UGameplayStatics::PlaySound2D(GetWorld(), SoundCue);
}


