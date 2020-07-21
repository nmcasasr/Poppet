// Fill out your copyright notice in the Description page of Project Settings.


#include "Poppet_Character.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Engine.h"
#include <GameFramework/Actor.h>
#include "Weapons/Poppet_Weapon.h"
#include "Components/CapsuleComponent.h"
#include "Components/Poppet_HealthComponent.h"
#include "Core/Poppet_GameMode.h"
#include "Core/Poppet_BarrelDamage.h"
#include "Particles/ParticleSystem.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/CheatManager.h"
#include "Kismet/GameplayStatics.h"
#include "Core/Poppet_GameInstance.h"

// Sets default values
APoppet_Character::APoppet_Character()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	MeleeSocketName = "SCK_Melee";
	BurnSocketName = "SCK_Burn";
	bUserFirstPersonView = false;
	bIsCrouched = false;
	bIsKicking = false;
	bIsDashing = false;
	bCanDash = true;
	FPSCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("FPS_CameraComponent"));
	FPSCameraComponent->bUsePawnControlRotation = true;
	FPSCameraComponent->SetupAttachment(RootComponent);

	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>(TEXT("SprintArmComponent"));
	SpringArmComponent->bUsePawnControlRotation = true;
	SpringArmComponent->SetupAttachment(RootComponent);


	TPSCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("TPS_CameraComponent"));
	TPSCameraComponent->SetupAttachment(SpringArmComponent);

	MeleeDetectorComponent = CreateDefaultSubobject<UCapsuleComponent>(TEXT("MeleeDetectorComponent"));
	MeleeDetectorComponent->SetupAttachment(GetMesh(), MeleeSocketName);
	MeleeDetectorComponent->SetCollisionResponseToAllChannels(ECR_Ignore);
	MeleeDetectorComponent->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);
	MeleeDetectorComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	HealthComponent = CreateDefaultSubobject<UPoppet_HealthComponent>(TEXT("HealthComponent"));

	InitialBurnTime = 600.0f;
	MaxPowerUpDuration = 10.0f;
	bIsUsingPowerUp = false;
	PlayRate = 1.0f;
	PowerUpPlayRate = 2.0f;
}

// Called when the game starts or when spawned
void APoppet_Character::BeginPlay()
{
	Super::BeginPlay();
	CreateInitalWeapon();

	GameModeReference = Cast<APoppet_GameMode>(GetWorld()->GetAuthGameMode());

	GameInstanceReference = Cast<UPoppet_GameInstance>(GetWorld()->GetGameInstance());

	MeleeDetectorComponent->OnComponentBeginOverlap.AddDynamic(this, &APoppet_Character::MakeMeleeAction);
	
	HealthComponent->OnHealthChangeDelegate.AddDynamic(this, &APoppet_Character::OnHealthChange);
	
	BurnTime = InitialBurnTime;
	if (IsValid(GetMesh())) {
		MyAnimInstance = GetMesh()->GetAnimInstance();
	}
}

void APoppet_Character::CreateInitalWeapon()
{
	if (IsValid(InitialWeaponClass)) {
		CurrentWeapon = GetWorld()->SpawnActor<APoppet_Weapon>(InitialWeaponClass, GetActorLocation(), GetActorRotation());
		if (IsValid(CurrentWeapon))
		{
			CurrentWeapon->setCharacterOwner(this);
			CurrentWeapon->AttachToComponent(GetMesh(), FAttachmentTransformRules::SnapToTargetNotIncludingScale);
		}
	}
}

void APoppet_Character::MoveForward(float value)
{
	AddMovementInput(GetActorForwardVector() * value);
}

void APoppet_Character::MoveRight(float value)
{
	AddMovementInput(GetActorRightVector() * value);
}

void APoppet_Character::Jump()
{
	Super::Jump();
}

void APoppet_Character::StopJumping()
{
	Super::StopJumping();
}

void APoppet_Character::CrouchCharacter()
{

	if (!this->bIsCrouched) {
	Super::Crouch();
	this->bIsCrouched = true;
	FVector capsulePosition = GetCapsuleComponent()->GetComponentLocation();
	GetCapsuleComponent()->SetCapsuleHalfHeight(60, false);
	GetMesh()->SetRelativeLocation(FVector(0, 0,  -60));
	}
	else
	{
	Super::UnCrouch();
	FVector capsulePosition = GetCapsuleComponent()->GetComponentLocation();
	GetCapsuleComponent()->SetCapsuleHalfHeight(88, false);
	GetMesh()->SetRelativeLocation(FVector(0, 0, -88));
	this->bIsCrouched = false;
	}
	
}

void APoppet_Character::Dash()
{
	if (bCanDash) {
		bIsDashing = true;
		bCanDash = false;
		FVector launchVector = GetActorForwardVector();
		LaunchCharacter(launchVector * 3000, false, true);
		bIsDashing = false;
		GetWorld()->GetTimerManager().SetTimer(dDashingCoolDown, this, &APoppet_Character::restartDash, 3.0f, false);
	}
}

void APoppet_Character::restartDash()
{
	bCanDash = true;
	GetWorldTimerManager().ClearTimer(dDashingCoolDown);
}

void APoppet_Character::RestartLevel()
{
	UGameplayStatics::OpenLevel(this, FName(*GetWorld()->GetName()), false);
}

void APoppet_Character::StartShooting()
{
	if (IsValid(CurrentWeapon))
	{
		CurrentWeapon->StartShooting();

	}
}

void APoppet_Character::StopShooting()
{
	if (IsValid(CurrentWeapon))
	{
		CurrentWeapon->StopShooting();

	}
}

void APoppet_Character::StartMeele()
{
	UE_LOG(LogTemp, Warning, TEXT("Meele Attac"));
	if (bIsUsingPowerUp) {
	GetWorldSettings()->SetTimeDilation(0.4f);
	}
	
	bIsKicking = true;
}

void APoppet_Character::StopMeele()
{
	GetWorldSettings()->SetTimeDilation(1.0f);
	bIsKicking = false;
}

void APoppet_Character::OnHealthChange(UPoppet_HealthComponent * MyHealthComponent, AActor * DamagedActor, float Damage, const UDamageType * DamageType, AController * InstigatedBy, AActor * DamageCauser)
{
	const UPoppet_BarrelDamage* BarrelDamage = Cast<UPoppet_BarrelDamage>(DamageType);
	if (IsValid(BarrelDamage)) {
		GetWorld()->GetTimerManager().SetTimer(dBurnCoolDown, this, &APoppet_Character::CheckDamage, 0.1f, true);
		StartBurning();
	}
	if (HealthComponent->IsDead()) {
		if (IsValid(GameModeReference)) {
			GameModeReference->GameOver(this);
		}
		if (IsValid(GameInstanceReference))
		{
			GameInstanceReference->AddPlayerDeathToCounter();
		}
	}
}
void APoppet_Character::CheckDamage()
{
	if (HealthComponent->IsDead()) {
		GetWorld()->GetTimerManager().ClearTimer(dBurnCoolDown);
		if (IsValid(GameModeReference)) {
			GameModeReference->GameOver(this);
		}
		if (IsValid(GameInstanceReference))
		{
			GameInstanceReference->AddPlayerDeathToCounter();
		}
	}
	if (--BurnTime <= 0) {
		GetWorld()->GetTimerManager().ClearTimer(dBurnCoolDown);
		BurnTime = InitialBurnTime;
	}
}
void APoppet_Character::StartBurning()
{
	if (IsValid(BurnEffect)) {
		UGameplayStatics::SpawnEmitterAttached(BurnEffect,this->GetMesh(), BurnSocketName);

	}
}
// Called every frame
void APoppet_Character::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (bIsUsingPowerUp) {
		UpdatePowerUpDuration(DeltaTime);
	}

}

// Called to bind functionality to input
void APoppet_Character::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent->BindAxis("MoveForward", this, &APoppet_Character::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &APoppet_Character::MoveRight);

	PlayerInputComponent->BindAxis("LookUp", this, &ACharacter::AddControllerPitchInput);
	PlayerInputComponent->BindAxis("LookRight", this, &ACharacter::AddControllerYawInput);

	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &APoppet_Character::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &APoppet_Character::StopJumping);

	PlayerInputComponent->BindAction("Crouch", IE_Pressed, this, &APoppet_Character::CrouchCharacter);

	PlayerInputComponent->BindAction("Dash", IE_Pressed, this, &APoppet_Character::Dash);

	PlayerInputComponent->BindAction("Restart", IE_Pressed, this, &APoppet_Character::RestartLevel);

	PlayerInputComponent->BindAction("Shoot", IE_Pressed, this, &APoppet_Character::StartShooting);
	PlayerInputComponent->BindAction("Shoot", IE_Released, this, &APoppet_Character::StopShooting);

	PlayerInputComponent->BindAction("Melee", IE_Pressed, this, &APoppet_Character::StartMeele);
	PlayerInputComponent->BindAction("Melee", IE_Released, this, &APoppet_Character::StopMeele);	

	PlayerInputComponent->BindAction("Menu", IE_Pressed, this, &APoppet_Character::GoToMainMenu);

}

void APoppet_Character::AddItem(FName newItem)
{
	Items = newItem;
}
void APoppet_Character::DeleteItem()
{
	Items = "";
}
bool APoppet_Character::HasKey(FName itemTag)
{
	return Items == itemTag;
}

void APoppet_Character::setMeleeDetectorCollision(ECollisionEnabled::Type NewColissionState)
{
	MeleeDetectorComponent->SetCollisionEnabled(NewColissionState);
}

void APoppet_Character::MakeMeleeAction(UPrimitiveComponent * OverlappedComponent, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	if (IsValid(OtherActor)) {
		OtherActor->Destroy();
	}
}

void APoppet_Character::GainPowerUp()
{
	if (bIsUsingPowerUp) {
		return;
	}
	if (IsValid(MyAnimInstance) && IsValid(PowerUpMontage)) {
		GetCharacterMovement()->MaxWalkSpeed = 0.0f;
		const float PowerUpAnimationDuration = MyAnimInstance->Montage_Play(PowerUpMontage, PlayRate);
		GetWorld()->GetTimerManager().SetTimer(TimerHandle_BeginPowerUp, this, &APoppet_Character::BeginPowerUp, PowerUpAnimationDuration, false);
	}
	else {
		BeginPowerUp();
	}
	BP_StartPowerUp();
}

void APoppet_Character::UpdatePowerUpDuration(float Value)
{
	CurrentPowerUpDuration = FMath::Clamp(CurrentPowerUpDuration - Value, 0.0f, MaxPowerUpDuration);

	if (CurrentPowerUpDuration == 0.0f) {
		bIsUsingPowerUp = false;
		GetCharacterMovement()->MaxWalkSpeed = 400;
		GetWorldSettings()->SetTimeDilation(1.0f);
		PlayRate = 1.0f;
		BP_StopPowerUp();
	}
}

void APoppet_Character::BeginPowerUp()
{
	CurrentPowerUpDuration = MaxPowerUpDuration;
	GetCharacterMovement()->MaxWalkSpeed = 2000.0f;
	PlayRate = PowerUpPlayRate;
	bIsUsingPowerUp = true;
}

void APoppet_Character::GoToMainMenu()
{
	if (IsValid(GameInstanceReference)) {
		GameInstanceReference->SaveData();
	}
	UGameplayStatics::OpenLevel(GetWorld(), FName("Menu"));

}
