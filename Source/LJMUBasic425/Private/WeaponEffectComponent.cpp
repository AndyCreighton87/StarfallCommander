#include "WeaponEffectComponent.h"

#include "BaseShip.h"
#include "CombatShip.h"
#include "WeaponEffect.h"

UWeaponEffectComponent::UWeaponEffectComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UWeaponEffectComponent::BeginPlay()
{
	Super::BeginPlay();
}

void UWeaponEffectComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

// Spawn a new projectile
void UWeaponEffectComponent::FireProjectile()
{
	if(ProjectileClass)
	{
		const FVector tPos = GetComponentLocation();
		const FRotator tRot = GetComponentRotation();
		const FActorSpawnParameters tParams;
		const auto tProjectile = GetWorld()->SpawnActor<AWeaponEffect>(ProjectileClass, tPos, tRot, tParams);
		ACombatShip* tOwningShip = Cast<ACombatShip>(GetOwner());
		tProjectile->Init(tOwningShip);
	}

}

