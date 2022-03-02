#include "Asteroid.h"
#include "Components/SphereComponent.h"

AAsteroid::AAsteroid()
{
	PrimaryActorTick.bCanEverTick = false;

	// Create components
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(FName("Mesh"));
	CollisionSphere = CreateDefaultSubobject<USphereComponent>(FName("Collision Sphere"));

	RootComponent = CollisionSphere;
	Mesh->SetupAttachment(CollisionSphere);
}

// Called when the game starts or when spawned
void AAsteroid::BeginPlay()
{
	Super::BeginPlay();
}

EAllegiance AAsteroid::GetAllegiance()
{
	return Allegiance;
}