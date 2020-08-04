// Fill out your copyright notice in the Description page of Project Settings.


#include "Poppet_Item.h"
#include "Components/SphereComponent.h"
#include "Sound/SoundCue.h"
#include "Kismet/GameplayStatics.h"
#include "..\..\Public\Items\Poppet_Item.h"
#include "Poppet_Character.h"
// Sets default values
APoppet_Item::APoppet_Item()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	MainColliderComponent = CreateDefaultSubobject<USphereComponent>(TEXT("MainColliderComponent"));
	RootComponent = MainColliderComponent;
	MainColliderComponent->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	MainColliderComponent->SetCollisionResponseToAllChannels(ECR_Ignore);
	MainColliderComponent->SetCollisionResponseToChannel(ECC_WorldStatic, ECR_Block);
	MainColliderComponent->SetCollisionResponseToChannel(ECC_WorldDynamic, ECR_Block);
	MainColliderComponent->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);


}

// Called when the game starts or when spawned
void APoppet_Item::BeginPlay()
{
	Super::BeginPlay();
	
}

void APoppet_Item::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void APoppet_Item::Pickup(APoppet_Character* PickUpActor)
{
	BP_Pickup(PickUpActor);
	PlaySound(PickUpSound);
}

void APoppet_Item::NotifyActorBeginOverlap(AActor * OtherActor)
{
	Super::NotifyActorBeginOverlap(OtherActor);

	if (IsValid(OtherActor)) {
		APoppet_Character* OverlapedCharacter = Cast<APoppet_Character>(OtherActor);
		if (IsValid(OverlapedCharacter)) {
			Pickup(OverlapedCharacter);
		}
	}
	
}

void APoppet_Item::PlaySound(USoundCue * SoundCue, bool bIs3D, FVector SoundLocation)
{
	if (!IsValid(SoundCue))
	{
		return;
	}
	if (bIs3D)
	{
		UGameplayStatics::PlaySoundAtLocation(GetWorld(), SoundCue, SoundLocation);
	}
	else {
		UGameplayStatics::PlaySound2D(GetWorld(), SoundCue);
	}
}

