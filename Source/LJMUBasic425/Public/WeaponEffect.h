/// A poorly named class. "Projectile" would be more appropriate.
/// Weapon Effect represents a projectile within the game, they are spawned from the
/// Weapon Effect Component. The projectile itself, and the majority of it's functionality
/// was from an asset pack. This class simply manages passing damage data from ship to ship
/// and it's lifetime.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "WeaponEffect.generated.h"

UCLASS()
class LJMUBASIC425_API AWeaponEffect : public AActor
{
	GENERATED_BODY()
	
public:	
	AWeaponEffect();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

public:
	// Received from owning ship. Delivered to target on successful hit.
	UPROPERTY(BlueprintReadWrite, Category = "Weapon Effect")
	float Damage;

	// The distance the projectile will travel before destroying itself
	UPROPERTY(EditAnywhere, Category = "Weapon Effect")
	float Lifetime = 10000.0f;
	
private:
	UPROPERTY()
	class ACombatShip* OwningShip;

	UPROPERTY()
	float DistanceTravelled;

	UPROPERTY()
	FVector StartingPos;
	
public:
	UFUNCTION(BlueprintCallable, Category = "Weapon Effect")
	void Init(class ACombatShip* pShip);

	UFUNCTION(BlueprintCallable, Category = "Weapon Effect")
	ACombatShip* GetOwningShip();

private:
	UFUNCTION()
	void CheckShouldDie();
};
