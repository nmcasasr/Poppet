// Fill out your copyright notice in the Description page of Project Settings.


#include "Poppet_HealerBot.h"
#include "Components/StaticMeshComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Poppet_Character.h"
#include "NavigationSystem/Public/NavigationSystem.h"
#include "NavigationSystem/Public/NavigationPath.h"
#include "Particles/ParticleSystem.h"
#include "Particles/ParticleSystemComponent.h"
// Sets default values
APoppet_HealerBot::APoppet_HealerBot()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	MainMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MainMeshComponent"));
	MainMeshComponent->SetCanEverAffectNavigation(false);
	MainMeshComponent->SetSimulatePhysics(true);
	RootComponent = MainMeshComponent;
	MinDistanceToPlayer = 150.0f;
	ForceMagnitude = 3000.0f;
	Item = "KeyA";
	TraceParamName = "ChargeBeam_Target";
	TraceParamNameSource = "ChargeBeam_Source";
	SocketName = "particle_socket";

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

	NextPathPoint = GetNextPathPoint();
	
}

FVector APoppet_HealerBot::GetNextPathPoint()
{
	if (IsValid(PlayerCharacter))
	{
		UNavigationPath* NavigationPath = UNavigationSystemV1::FindPathToActorSynchronously(GetWorld(), GetActorLocation(), PlayerCharacter);
		if (NavigationPath->PathPoints.Num() > 1)
		{
			UE_LOG(LogTemp, Warning, TEXT("VALID CHARACTER"));
			return NavigationPath->PathPoints[1];
		}
		else {
			return GetActorLocation();
		}
	}
		return GetActorLocation();

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
		UE_LOG(LogTemp, Warning, TEXT("Add force"));
		MainMeshComponent->AddForce(ForceDirection, NAME_None ,true);
	}
	//DrawDebugSphere(GetWorld(), NextPathPoint, 30.0f, 15, FColor::Purple, false, 0.0f, 0, 1.0f);
	if (IsValid(PlayerCharacter))
	{
		FVector PlayerLocation = PlayerCharacter->GetActorLocation();
		float DistanceToPlayer = (GetActorLocation() - PlayerLocation).Size();
		if (DistanceToPlayer <= MinDistanceToPlayer) {
			PlayerCharacter->AddItem(Item);
			if (IsValid(TraceEffect)) {
				//UParticleSystemComponent* TracerComponent = UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), TraceEffect, GetActorLocation());
				//UParticleSystemComponent* TracerComponent = UGameplayStatics::SpawnEmitterAttached(TraceEffect, MainMeshComponent, SocketName);
				if (IsValid(TracerComponent)) {
					TracerComponent->SetVectorParameter(TraceParamName, PlayerLocation);
					TracerComponent->SetVectorParameter(TraceParamNameSource, GetActorLocation());
				}
			}
		}
	}
}


