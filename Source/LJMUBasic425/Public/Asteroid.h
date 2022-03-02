/// The Asteroid class inherits from IMinable and IShowOnMinimap.
/// Allows Asteroids to be mined by miners. Holds an allegiance to determine
/// its colour on the minimap

#pragma once

#include "CoreMinimal.h"
#include "IMinable.h"
#include "IShowOnMinimap.h"
#include "GameFramework/Actor.h"


#include "Asteroid.generated.h"

UCLASS()
class LJMUBASIC425_API AAsteroid : public AActor, public IMinable, public IShowOnMinimap
{
	GENERATED_BODY()
	
public:	
	AAsteroid();

protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY(EditAnywhere, Category = "Asteroid");
	class UStaticMeshComponent* Mesh;

	UPROPERTY(EditAnywhere, Category = "Asteroid")
	class USphereComponent* CollisionSphere;

	UPROPERTY(EditAnywhere, Category = "Asteroid")
	EAllegiance Allegiance;

public:
	virtual EAllegiance GetAllegiance() override;

};
