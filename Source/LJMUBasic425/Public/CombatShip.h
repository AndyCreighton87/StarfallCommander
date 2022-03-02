/// Combat Ship is a subclass of BaseShip and serves as a base class itself to all ships
/// capable of dealing damage in the game. It includes a weapon effect component, a custom
/// component responsible for spawning projectiles.

#pragma once

#include "CoreMinimal.h"
#include "BaseShip.h"
#include "CombatShipData.h"
#include "WeaponEffectComponent.h"
#include "CombatShip.generated.h"

UCLASS()
class LJMUBASIC425_API ACombatShip : public ABaseShip
{
	GENERATED_BODY()

public:
	ACombatShip(const FObjectInitializer& ObjectInitializer);

protected:
	virtual void BeginPlay() override;
	
private:
	// Struct containing all combat data (damage, attack speed etc) pertaining to ship
	UPROPERTY(EditAnywhere, Category = "Ship | Combat")
	FCombatShipData CombatData;

	// The attack target
	UPROPERTY()
	ABaseShip* TargetShip;

	// Responsible for spawning projectiles
	UPROPERTY(EditAnywhere, Category = "Ship | Weapon Effect")
	UWeaponEffectComponent* WeaponEffectComponent;

public:
	virtual void Tick(float DeltaSeconds) override;

	// Aggro is managed largely through the Behavior Tree.
	// When an enemy ship comes into the combat ships Aggro Range, if they
	// are not currently following an order they will pursue and attack that ship.
	UFUNCTION(BlueprintCallable, Category = "Combat Ship")
	void ManageAggro(const TArray<AActor*>& pActors);

	UFUNCTION(BlueprintPure, Category = "Combat Ship")
	float GetDamage() const;

	UFUNCTION(BlueprintCallable, Category = "Combat Ship")
	void SetTargetShip(ABaseShip* pShip);

	UFUNCTION(BlueprintCallable, Category = "Combat Ship")
	float GetWeaponRange();

	UFUNCTION(BlueprintCallable, Category = "Combat Ship")
	float GetWeaponCooldown();

	UFUNCTION(BlueprintCallable, Category = "Combat Ship")
	float GetAggroRange();

	UFUNCTION(BlueprintCallable, Category = "Combat Ship")
	ABaseShip* GetTargetShip();

	UFUNCTION(BlueprintCallable, Category = "Combat Ship")
	bool IsTargetInRange();

	UFUNCTION()
	void FireWeapon() const;

	UFUNCTION(BlueprintCallable, Category = "Combat Ship")
	FCombatShipData GetCombatData();
};
