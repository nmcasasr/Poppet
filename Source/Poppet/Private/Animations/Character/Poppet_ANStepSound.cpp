// Fill out your copyright notice in the Description page of Project Settings.


#include "Poppet_ANStepSound.h"
#include "..\..\..\Public\Animations\Character\Poppet_ANStepSound.h"
#include "Poppet_Character.h"

void UPoppet_ANStepSound::Notify(USkeletalMeshComponent * MeshComp, UAnimSequenceBase * Animation)
{
	AActor* CharacterActor = MeshComp->GetOwner();
	if (IsValid(CharacterActor)) {
		APoppet_Character* Character = Cast<APoppet_Character>(CharacterActor);
		if (IsValid(Character)) {
			Character->PlayStepSound();
		}
	}
}
