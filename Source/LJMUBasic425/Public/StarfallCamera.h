/// StarfallCamera is the default Pawn. The player has direct control over the camera,
/// using WASD keys or moving the mouse towards the edge of the screen will cause the
/// camera to pan.
///
/// Also uses a BoxComponent and invisible walls to ensure player remains within bounds of
/// the level.

#pragma once

#include "CoreMinimal.h"
#include "StarfallHUD.h"
#include "StarfallPlayerController.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/BoxComponent.h"
#include "GameFramework/Actor.h"
#include "GameFramework/FloatingPawnMovement.h"
#include "StarfallCamera.generated.h"

UCLASS()
class LJMUBASIC425_API AStarfallCamera : public APawn
{
	GENERATED_BODY()
	
public:	
	AStarfallCamera(const FObjectInitializer& ObjectInitializer);

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;

public:
	// Components
	// Box collider used for collision with level bounds
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera")
	UBoxComponent* Target;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Camera")
	USpringArmComponent* SpringArm;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Camera")
	UCameraComponent* Camera;
	
private:
	UPROPERTY()
	UFloatingPawnMovement* MovementComponent;
	
	UPROPERTY(EditAnywhere, Category = "Camera")
	float CameraSpeed;

	// The amount of space between the mouse cursor and edge of screen before
	// the camera starts moving.
	UPROPERTY(EditAnywhere, Category = "Camera")
	float Margin;

	UPROPERTY()
	AStarfallPlayerController* PlayerController;
	
public:
	UFUNCTION(BlueprintCallable, Category = "Starfall Camera")
	void MoveRight(const float pMagnitude);

	UFUNCTION(BlueprintCallable, Category = "Starfall Camera")
	void MoveUp(const float pMagnitude);
	
private:
	UFUNCTION()
	void ProcessMovement();
	

};
