#include "BaseShip.h"

#include "HealthComponent.h"
#include "ResourceManager.h"
#include "StarfallPlayerController.h"
#include "UniqueActivatable.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "Components/BoxComponent.h"
#include "GameFramework/FloatingPawnMovement.h"
#include "Kismet/GameplayStatics.h"
#include "Particles/ParticleSystemComponent.h"


// Sets default values
ABaseShip::ABaseShip(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	PrimaryActorTick.bCanEverTick = true;

	// Creation of the components.
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(FName("Mesh"));
	SelectionRing = CreateDefaultSubobject<UWidgetComponent>(FName("Selection Ring"));
	HealthComponent = CreateDefaultSubobject<UHealthComponent>(FName("Health Bar"));

	BoxCollider = CreateDefaultSubobject<UBoxComponent>(FName("Collider"));
	BoxCollider->SetGenerateOverlapEvents(true);
	
	MovementComponent = ObjectInitializer.CreateDefaultSubobject<UFloatingPawnMovement>(this, TEXT("MovementComponent"));
	MovementComponent->SetCanEverAffectNavigation(true);

	// Component Hierarchy
	RootComponent = BoxCollider;
	Mesh->SetupAttachment(BoxCollider);
	HealthComponent->AttachToComponent(Mesh, FAttachmentTransformRules::KeepRelativeTransform);
	SelectionRing->AttachToComponent(Mesh, FAttachmentTransformRules::KeepRelativeTransform);
	SelectionRing->SetVisibility(false);
}

// Initial setup. All pretty self explanatory. 

void ABaseShip::BeginPlay()
{
	Super::BeginPlay();
	
	Blackboard = UAIBlueprintHelperLibrary::GetBlackboard(this);
	HealthComponent->OnDeathDelegate.AddDynamic(this, &ABaseShip::ManageDeath);
	MovementComponent->MaxSpeed = ShipData.MovementSpeed;
	CreateAbilities();
	CreateOrders();
	SetUpThrusters();
}

// Called every frame
void ABaseShip::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	ManageThrusters();
}

// Called to bind functionality to input
void ABaseShip::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

// When a ship is selected - show the Selection Widget and Health Bar
void ABaseShip::OnSelect()
{
	SelectionRing->SetVisibility(true);
	HealthComponent->ShowHealthBar();
}

// When a ship is deselected - hide both
void ABaseShip::OnDeselect()
{
	SelectionRing->SetVisibility(false);
	HealthComponent->HideHealthBar();
}

EAllegiance ABaseShip::GetAllegiance()
{
	return Allegiance;
}

void ABaseShip::SetAllegiance(EAllegiance pAllegiance)
{
	Allegiance = pAllegiance;
}

// I'm not 100% sure where to talk about this, but here seems as good a place as any.
// How I managed dealing damage, When a ship fires a projectile, it stores the damage
// value within that projectile. Then when/if the projectile hits, ReceiveDamage is called
// passing that value through to here.
// Each point of armour a ship posses offers it a 10% reduction in damage. While this is
// fine within the confines of the project, this system would need more attention if the game
// were to expand as there is potential for 0 damage (if a ship has 10 armour)
void ABaseShip::ReceiveDamage(float pDamage)
{
	const float tDamageReduction =  pDamage / (ShipData.Armour * 10.0f);
	const float tFinalDamage = pDamage - tDamageReduction;
	HealthComponent->ReduceHealth(tFinalDamage);
}

// Spawning Activatables
void ABaseShip::CreateOrders()
{
	for (auto entry : OrdersClasses)
	{
		AOrder* tOrder = GetWorld()->SpawnActor<AOrder>(entry);
		tOrder->Init(this);
		Orders.Add(tOrder);
	}

	for (auto entry : UniqueOrderClasses)
	{
		AUniqueActivatable* tUnique = GetWorld()->SpawnActor<AUniqueActivatable>(entry);
		tUnique->Init(this);
		UniqueOrders.Add(tUnique);
	}
}

void ABaseShip::CreateAbilities()
{
	for (auto entry : AbilitiesClasses)
		Abilities.Add(GetWorld()->SpawnActor<AAbility>(entry));
}

// The thrusters are managed based upon the velocity of the ship.
void ABaseShip::ManageThrusters()
{
	if (MovementComponent->Velocity.Size() > 0 && !bThrustersOn)
	{
		bThrustersOn = true;
		for (const auto entry : Thrusters)
			entry->SetVisibility(bThrustersOn);

	}
	else if (MovementComponent->Velocity.Size() == 0 && bThrustersOn)
	{
		bThrustersOn = false;
		for (const auto entry : Thrusters)
			entry->SetVisibility(bThrustersOn);
	}
}

// When a ship dies, spawn an explosion, invoke the delegate and remove from the players selection.
// In the majority of cases, I have simply instantiated and destroyed actors as and when needed.
// I understand this is not the most optimal way to do this, and an object pool that combines a
// a starting pool with the ability to instantiate additional ships if the pool would ever go out
// of bounds would be best. Due to time constraints I was unable to do this, the good new is that
// the performance hit does not seem to be much.S
void ABaseShip::ManageDeath()
{
	const FActorSpawnParameters tSpawnParams;
	GetWorld()->SpawnActor<AActor>(DeathParticle, GetActorLocation(), GetActorRotation(), tSpawnParams);
	bIsDead = true;
	ShipDeathDelegate.Broadcast(this);
	
	// I attempted to set up a delegate to manage this. When the ship was initially added to the selection
	// the Player Controller would bind to the Death Delegate (and unbind when unselected). Then when death
	// occured it would remove the ship from the selection in its own end. However, I could not work out
	// how to make a delegate within an Interface work. And without that, I would need to cast to ABaseShip within
	// Player Controller to make the binding in the first place. Thus, I have opted for the less elegant approach
	// of calling the player controller and removing it from here. It works well.
	AStarfallPlayerController* tPlayerController = Cast<AStarfallPlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
	tPlayerController->RemoveFromSelection(this);

	// Reduce population
	tPlayerController->GetResourceManager()->DecreasePopulation(ShipData.PopulationCost);
	
	Destroy();
}

// Returns all Orders, Unique Orders & Abilities
TArray<TScriptInterface<IActivatable>> ABaseShip::GetAllActivatables()
{
	TArray<TScriptInterface<IActivatable>> tActivatable;
	tActivatable.Append(Orders);
	tActivatable.Append(UniqueOrders);
	tActivatable.Append(Abilities);
	return tActivatable;
}

FSelectableData ABaseShip::GetSelectableData()
{
	return SelectableData;
}

// This was a very inelegant solution. The problem was that I needed to issue an
// order for ships that corresponded to the right mouse button being pressed.
// This needed to happen outside of the Behaviour Tree, which was based in Blueprints.
// The player controller calls this function. Not enough thought went into the planning
// stages of this, and by the time I got around to it, the main order and ability system
// had been fully integrated (minus this). As a result, I've used a switch statement to
// activate the relevant order. A map would have been better, holding the Activatable Type
// and the order as a pair, however doing so at this point would require a full rework of the
// system as it relies on Arrays.
void ABaseShip::IssueOrder(EOrders pOrder)
{
	switch (pOrder)
	{
	case EOrders::Move:
		for (const auto entry : Orders)
		{
			if (entry->GetActivitableData().DisplayName == "Move")
			{
				entry->OnActivate();
				break;
			}
		}
		break;
	case EOrders::Attack:
		for (const auto entry : Orders)
		{
			if (entry->GetActivitableData().DisplayName == "Attack")
			{
				entry->OnActivate();
				break;
			}
		}
		break;

	case EOrders::Mine:
		for (const auto entry : Orders)
		{
			if (entry->GetActivitableData().DisplayName == "Mine")
			{
				entry->OnActivate();
				break;
			}
		}

		default:
			break;
	}
}