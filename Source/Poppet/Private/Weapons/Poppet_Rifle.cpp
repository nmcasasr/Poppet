// Fill out your copyright notice in the Description page of Project Settings.


#include "Poppet_Rifle.h"
#include "Weapons/Poppet_Proyectile.h"
#include "GameFramework/Character.h"
#include "Components/SkeletalMeshComponent.h"
#include "GameFramework/Pawn.h"
#include "Poppet_Character.h"
APoppet_Rifle::APoppet_Rifle() {

	MuzzleSocketName = "SCK_Muzzle";
}

void APoppet_Rifle::StartShooting()
{
	Super::StartShooting();
	if (IsValid(CurrentOwnerCharacter))
	{
	USkeletalMeshComponent* CharacterMeshComponent = CurrentOwnerCharacter->GetMesh();
	if (IsValid(CharacterMeshComponent))
	{
		APoppet_Character* PoppetCurrentCharacter = Cast<APoppet_Character>(CurrentOwnerCharacter);

		FVector MuzzleSocketLocation = CharacterMeshComponent->GetSocketLocation(MuzzleSocketName);
		APawn* Pawn = GetWorld()->GetFirstPlayerController()->GetPawn();
		FRotator PawnRotation = Pawn->GetBaseAimRotation();
		FRotator MuzzleSocketRotation = CharacterMeshComponent->GetSocketRotation(MuzzleSocketName);
		FName tag1 = "KeyA";
		FName tag2 = "KeyB";
		if (PoppetCurrentCharacter->HasKey(tag1)) {
		APoppet_Proyectile* CurrentProyectile = GetWorld()->SpawnActor<APoppet_Proyectile>(ProyectileClass, MuzzleSocketLocation, PawnRotation);
		CurrentProyectile->SpawnObject(tag1);
		PoppetCurrentCharacter->DeleteItem();
		}
		else if (PoppetCurrentCharacter->HasKey(tag2)) {
		APoppet_Proyectile* CurrentProyectile = GetWorld()->SpawnActor<APoppet_Proyectile>(ProyectileClass, MuzzleSocketLocation, PawnRotation);
		CurrentProyectile->SpawnObject(tag2);
		PoppetCurrentCharacter->DeleteItem();
		}
		
	}
	}
}
void APoppet_Rifle::StopShooting()
{
	Super::StopShooting();
}
