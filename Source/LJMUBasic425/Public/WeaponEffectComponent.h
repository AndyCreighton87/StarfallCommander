/// Custom component designed to spawn projectiles (poorly named again, sorry).
/// The majority of the projectile functionality is handed in blueprints (from an asset
/// pack) and was not coded by myself. This class simply manages creating them.
#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "WeaponEffectComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class LJMUBASIC425_API UWeaponEffectComponent : public USceneComponent
{
	GENERATED_BODY()

public:	
	UWeaponEffectComponent();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon Effect")
	TSubclassOf<class AActor> ProjectileClass;
	
	UFUNCTION(BlueprintCallable, Category = "Weapon Effect")
	void FireProjectile();
};
