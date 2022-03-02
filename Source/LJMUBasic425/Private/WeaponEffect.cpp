#include "WeaponEffect.h"

#include "CombatShip.h"

AWeaponEffect::AWeaponEffect()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AWeaponEffect::BeginPlay()
{
	Super::BeginPlay();

	StartingPos = GetActorLocation();
}

void AWeaponEffect::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	CheckShouldDie();
}

// Upon creation get damage.
void AWeaponEffect::Init(ACombatShip* pShip)
{
	OwningShip = pShip;
	Damage = OwningShip->GetDamage();
}

ACombatShip* AWeaponEffect::GetOwningShip()
{
	return OwningShip;
}

// Check if the distance travelled is greater than lifetime. If it is, destroy actor
void AWeaponEffect::CheckShouldDie()
{
	if ((GetActorLocation() - StartingPos).Size() >= Lifetime)
		Destroy();
}

