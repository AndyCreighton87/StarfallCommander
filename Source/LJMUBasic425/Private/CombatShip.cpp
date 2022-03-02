// Fill out your copyright notice in the Description page of Project Settings.


#include "CombatShip.h"

#include "WeaponEffect.h"
#include "BehaviorTree/BlackboardComponent.h"


ACombatShip::ACombatShip(const FObjectInitializer& ObjectInitializer) : ABaseShip(ObjectInitializer)
{
	// Set up Weapon Effect Component
	WeaponEffectComponent = CreateDefaultSubobject<UWeaponEffectComponent>(FName("Weapon Effect"));
	WeaponEffectComponent->SetupAttachment(Mesh);
}

void ACombatShip::BeginPlay()
{
	Super::BeginPlay();
}

void ACombatShip::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
}

// Attack enemy ships that come within Aggro Range
void ACombatShip::ManageAggro(const TArray<AActor*>& pActors)
{
	if (TargetShip)
		return;
	
	for (const auto entry : pActors)
	{
		ABaseShip* tShip = Cast<ABaseShip>(entry);
		
		if (tShip->GetAllegiance() != Allegiance)
		{
			TargetShip = tShip;
			Blackboard->SetValueAsObject("TargetShip", tShip);
			Blackboard->SetValueAsEnum("State", static_cast<uint8>(EOrders::Attack));
			return;
		}
	}
}

float ACombatShip::GetDamage() const
{
	return CombatData.AttackDamage;
}

void ACombatShip::SetTargetShip(ABaseShip* pShip)
{
	TargetShip = pShip;
}

float ACombatShip::GetWeaponRange()
{
	return CombatData.AttackRange;
}

float ACombatShip::GetWeaponCooldown()
{
	return 1.0f / CombatData.AttackSpeed;
}

float ACombatShip::GetAggroRange()
{
	return CombatData.AggroRange;
}

ABaseShip* ACombatShip::GetTargetShip()
{
	return TargetShip;
}

// Checks if TargetShip is within the CombatShips Attack Range
bool ACombatShip::IsTargetInRange()
{
	if (TargetShip)
	{
		const float tDistance = (TargetShip->GetActorLocation() - this->GetActorLocation()).Size();

		if (tDistance <= CombatData.AttackRange * 100.0f)
			return true;
	}

	return false;
}

void ACombatShip::FireWeapon() const
{
	WeaponEffectComponent->FireProjectile();
}

FCombatShipData ACombatShip::GetCombatData()
{
	return CombatData;
}
