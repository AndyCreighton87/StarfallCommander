// Fill out your copyright notice in the Description page of Project Settings.


#include "StarfallCamera.h"

#include "StarfallPlayerController.h"
#include "Engine/UserInterfaceSettings.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AStarfallCamera::AStarfallCamera(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//Set up components
	Target = CreateDefaultSubobject<UBoxComponent>(TEXT("Target"));
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));

	SpringArm->bDoCollisionTest = false;
	
	RootComponent = Target;
	SpringArm->SetupAttachment(RootComponent);
	Camera->SetupAttachment(SpringArm);

	//Init Movement Component
	MovementComponent = ObjectInitializer.CreateDefaultSubobject<UFloatingPawnMovement>(this, TEXT("Starfall Camera"));
	MovementComponent->SetCanEverAffectNavigation(false);
}

void AStarfallCamera::BeginPlay()
{
	Super::BeginPlay();
	
	PlayerController = Cast<AStarfallPlayerController>(GetController());
	MovementComponent->MaxSpeed = CameraSpeed;
}

void AStarfallCamera::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	ProcessMovement();
}

void AStarfallCamera::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	
	check(PlayerInputComponent);

	//Axis Binding
	PlayerInputComponent->BindAxis(TEXT("MoveUp"), this, &AStarfallCamera::MoveUp);
	PlayerInputComponent->BindAxis(TEXT("MoveRight"), this, &AStarfallCamera::MoveRight);
}

//Check Mouse Pos against screen dimensions, pan camera accordingly
void AStarfallCamera::ProcessMovement()
{
	int tScreenWidth;
	int tScreenHeight;
	FVector2D tMousePos;
	
	PlayerController->GetViewportSize(tScreenWidth, tScreenHeight);
	PlayerController->GetMousePosition(tMousePos.X, tMousePos.Y);
	
	if (tMousePos.X <= Margin)
		MoveRight(-1.0f);
	else if (tMousePos.X >= tScreenWidth - Margin)
		MoveRight(1.0f);
	
	if (tMousePos.Y <= Margin)
		MoveUp(1.0f);
	else if (tMousePos.Y >= tScreenHeight - Margin)
		MoveUp(-1.0f);
}

void AStarfallCamera::MoveRight(const float pMagnitude)
{
	if (pMagnitude != 0)
		AddMovementInput(FVector(0.0f, 1.0f, 0.0f) * CameraSpeed * GetWorld()->GetDeltaSeconds(), pMagnitude);
}

void AStarfallCamera::MoveUp(const float pMagnitude)
{
	if (pMagnitude != 0)
		AddMovementInput(FVector(1.0f, 0.0f, 0.0f) * CameraSpeed * GetWorld()->GetDeltaSeconds(), pMagnitude);
}