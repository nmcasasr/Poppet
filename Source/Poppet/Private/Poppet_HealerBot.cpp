// Fill out your copyright notice in the Description page of Project Settings.


#include "Poppet_HealerBot.h"
#include "Components/StaticMeshComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Poppet_Character.h"
#include "NavigationSystem/Public/NavigationSystem.h"
#include "NavigationSystem/Public/NavigationPath.h"
#include "Particles/ParticleSystem.h"
#include "Particles/ParticleSystemComponent.h"
#include "Items/Poppet_ItemSpawner.h"
// Sets default values
APoppet_HealerBot::APoppet_HealerBot()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	MainMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MainMeshComponent"));
	MainMeshComponent->SetCanEverAffectNavigation(false);
	MainMeshComponent->SetSimulatePhysics(true);
	RootComponent = MainMeshComponent;
	MinDistanceToPlayer = 250.0f;
	ForceMagnitude = 5000.0f;
	maxPlayerDistance = 600.0f;
	Item = "KeyA";
	TraceParamName = "ChargeBeam_Target";
	TraceParamNameSource = "ChargeBeam_Source";
	SocketName = "particle_socket";
	bIsInRange = false;
	LifeTime = 10.0f;

}

// Called when the game starts or when spawned
void APoppet_HealerBot::BeginPlay()
{
	Super::BeginPlay();
	TracerComponent = UGameplayStatics::SpawnEmitterAttached(TraceEffect, MainMeshComponent, SocketName);
	APawn* Character = UGameplayStatics::GetPlayerPawn(GetWorld(),0);
	if (IsValid(Character))
	{
		PlayerCharacter = Cast<APoppet_Character>(Character);
	}
	InitLifeTime = LifeTime;
	NextPathPoint = GetNextPathPoint();
	GetWorld()->GetTimerManager().SetTimer(TimerHandle_Spawn, this, &APoppet_HealerBot::DestroyItem, 1.0f, true);
}

FVector APoppet_HealerBot::GetNextPathPoint()
{
	FVector PlayerLocation = PlayerCharacter->GetActorLocation();
	float DistanceToPlayer = (GetActorLocation() - PlayerLocation).Size();
	if (IsValid(PlayerCharacter) && (DistanceToPlayer < maxPlayerDistance))
	{
		UNavigationPath* NavigationPath = UNavigationSystemV1::FindPathToActorSynchronously(GetWorld(), GetActorLocation(), PlayerCharacter);
		if (NavigationPath->PathPoints.Num() > 1)
		{
			return NavigationPath->PathPoints[1];
		}
		else {
			return GetActorLocation();
		}
	}
		return GetActorLocation();

}

void APoppet_HealerBot::DestroyItem()
{
	LifeTime--;
	if (LifeTime <= 0.0f) {
		if (IsValid(MySpawner)) {
			MySpawner->DeleteItem();
		}
		
		Destroy();
	}
	
}

// Called every frame
void APoppet_HealerBot::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	float DistanceToTarget = (GetActorLocation() - NextPathPoint).Size();

	if (DistanceToTarget <= MinDistanceToPlayer) {
		NextPathPoint = GetNextPathPoint();
	}
	else {
		FVector ForceDirection = NextPathPoint - GetActorLocation();
		ForceDirection.Normalize();
		ForceDirection *= ForceMagnitude;
		MainMeshComponent->AddForce(ForceDirection, NAME_None ,true);
	}
	if (IsValid(PlayerCharacter))
	{
		FVector PlayerLocation = PlayerCharacter->GetActorLocation();
		float DistanceToPlayer = (GetActorLocation() - PlayerLocation).Size();
		if (DistanceToPlayer <= MinDistanceToPlayer) {
			TracerComponent->ActivateSystem(true);
			PlayerCharacter->AddItem(Item);
			bIsInRange = true;
			LifeTime = InitLifeTime;
			if (IsValid(TraceEffect)) {
				if (IsValid(TracerComponent)) {
					TracerComponent->SetVectorParameter(TraceParamName, PlayerLocation);
					TracerComponent->SetVectorParameter(TraceParamNameSource, GetActorLocation());
				}
			}
		}
		else {
			TracerComponent->SetVectorParameter(TraceParamName, GetActorLocation());
			TracerComponent->SetVectorParameter(TraceParamNameSource, GetActorLocation());
			bIsInRange = false;
		}
	}
	
}


