// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Poppet_SpectatingCamera.generated.h"

class UStaticMeshComponent;

UENUM()
enum class EPoppet_SpectatingCameraType : uint8 {
	CameraType_None		UMETA(DisplayName = "None"),
	CameraType_Victory	UMETA(DisplayName = "Victory"),
	CameraType_GameOver UMETA(DisplayName = "Game Over")
};
UCLASS()
class POPPET_API APoppet_SpectatingCamera : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APoppet_SpectatingCamera();

	EPoppet_SpectatingCameraType GetCameraType() { return CameraType; }

protected:

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Spectating Camera")
	EPoppet_SpectatingCameraType CameraType;

protected:
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UStaticMeshComponent* SpectatingCameraComponent;

};
