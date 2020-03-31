// Fill out your copyright notice in the Description page of Project Settings.


#include "Poppet_Character.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Engine.h"
#include <GameFramework/Actor.h>

// Sets default values
APoppet_Character::APoppet_Character()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	bUserFirstPersonView = false;
	bIsCrouched = false;
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
}

// Called when the game starts or when spawned
void APoppet_Character::BeginPlay()
{
	Super::BeginPlay();
	
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
	}
	else
	{
	Super::UnCrouch();
	this->bIsCrouched = false;
	}
	
}

void APoppet_Character::Dash()
{
	if (bCanDash) {
		bIsDashing = true;
		bCanDash = false;
		FVector launchVector = GetActorRotation().Vector();
		LaunchCharacter(launchVector * 3000 * FVector(1, 1, 0), false, true);
		bIsDashing = false;
		GetWorld()->GetTimerManager().SetTimer(dDashingCoolDown, this, &APoppet_Character::restartDash, 3.0f, false);
	}
}

void APoppet_Character::restartDash()
{
	bCanDash = true;
	GetWorldTimerManager().ClearTimer(dDashingCoolDown);
}
// Called every frame
void APoppet_Character::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

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

}

