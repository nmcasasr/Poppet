// Fill out your copyright notice in the Description page of Project Settings.


#include "Poppet_ANSMelee.h"
#include "Poppet_Character.h"

void UPoppet_ANSMelee::NotifyBegin(USkeletalMeshComponent * MeshComp, UAnimSequenceBase * Animation, float TotalDuration)
{
	AActor* CharacterActor = MeshComp->GetOwner();
	if (IsValid(CharacterActor)) {
		APoppet_Character* Character = Cast<APoppet_Character>(CharacterActor);
		if (IsValid(Character)) {
			Character->setMeleeDetectorCollision(ECollisionEnabled::QueryOnly);
		}
	}
}

void UPoppet_ANSMelee::NotifyEnd(USkeletalMeshComponent * MeshComp, UAnimSequenceBase * Animation)
{
	AActor* CharacterActor = MeshComp->GetOwner();
		if (IsValid(CharacterActor)) {
			APoppet_Character* Character = Cast<APoppet_Character>(CharacterActor);
				if (IsValid(Character)) {
					Character->setMeleeDetectorCollision(ECollisionEnabled::NoCollision);
				}
		}
}
