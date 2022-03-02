
/// BaseShip is the largest class within the game, it serves as the blueprint for every
/// ship and as a result contains a lot of functionality.
/// Covering it in a summary is impossible, so I will make comments through the header
/// file and cpp upon important topics.
/// I would note however, that there certainly is scope to reduce the size of this class
/// through additional abstraction into components. The Health Component is a good example
/// of this.

#pragma once

#include "CoreMinimal.h"
#include "Ability.h"

#include "EAllegiance.h"
#include "IActivatable.h"
#include "ShipData.h"
#include "IBuildable.h"
#include "ISelectable.h"
#include "IShowOnMinimap.h"
#include "Order.h"
#include "SelectableData.h"
#include "Components/WidgetComponent.h"
#include "GameFramework/Pawn.h"
#include "BaseShip.generated.h"

UDELEGATE()
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnShipDeath, ABaseShip*, Ship);

UCLASS()
class LJMUBASIC425_API ABaseShip : public APawn, public IBuildable, public IShowOnMinimap, public ISelectable
{
	GENERATED_BODY()

public:
	ABaseShip(const FObjectInitializer& ObjectInitializer);
	
protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;
	
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Ship")
	class UFloatingPawnMovement* MovementComponent;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ship");
	class UStaticMeshComponent* Mesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ship")
	class UBoxComponent* BoxCollider;

	// AI state is managed through C++. Behaviour Tree and Blackboard Blueprints are
	// used in conjunction with custom tasks (also C++, mostly) to give functionality,
	// Most of the time the base ship will simply change a blackboard value from code.
	UPROPERTY(EditAnywhere,Category = "Ship | AI")
	class UBehaviorTree* BehaviorTree;
	
	class UBlackboardComponent* Blackboard;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Ship")
	EAllegiance Allegiance;

	// Health Component is a custom component, see it's own .h file for a better
	// description.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ship")
	TSubclassOf<class UHealthComponent> HealthComponentClass;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Ship");
	UHealthComponent* HealthComponent;

	// Activatables are managed using TSubClassOf to allow for easy customisation through
	// blueprints. At the beginning of the game, a ship will generate each Order and Ability
	// found within these arrays. This system would also allow for adding/removing activatables
	// at runtime (like if ship damage was local, engines could be destroyed and the move order
	// could be taken away), but that's well outside of the scope of this project.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ship")
	TArray<TSubclassOf<AOrder>> OrdersClasses;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ship")
	TArray<TSubclassOf<class AUniqueActivatable>> UniqueOrderClasses;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ship")
	TArray<TSubclassOf<AAbility>> AbilitiesClasses;

	// Thrusters were a strange one, feedback on this would be nice.
	// I wanted each ship to have a series of Thrusters that would activate and deactivate
	// as the ship moved. I used a particle system component for this.
	// The issue was that each ships mesh required a different number of thrusters. I think the
	// most was 5 and the least 1. How I managed this, was to attach the particle components to
	// the ship through blueprints (so, not inherited from this base class) and then grab a reference
	// to them on begin play. I'm not sure if this was the optimal approach.
	UPROPERTY(BlueprintReadWrite, Category = "Ship")
	TArray<class UParticleSystemComponent*> Thrusters; 
	
	UPROPERTY(BlueprintReadWrite, Category = "Ship")
	bool bThrustersOn = false;

	UPROPERTY(BlueprintReadOnly, Category = "Ship")
	bool bIsDead = false;

	// A one parameter dynamic delegate, used to pass itself as a reference upon death.
	UPROPERTY()
	FOnShipDeath ShipDeathDelegate;
	
protected:
	// The UI indicator to show the ship has been selected.
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Ship | Selection")
	UWidgetComponent* SelectionRing;

private:
	// Structs - see more on each in their respective .h files
	UPROPERTY(EditAnywhere, Category = "Ship | Data")
	FSelectableData SelectableData;
	
	UPROPERTY(EditAnywhere, Category = "Ship | Data");
	FShipData ShipData;
	
	UPROPERTY()
	TArray<TScriptInterface<IActivatable>> Abilities;
	
	UPROPERTY()
	TArray<TScriptInterface<IActivatable>> Orders;

	UPROPERTY()
	TArray<TScriptInterface<IActivatable>> UniqueOrders;

	UPROPERTY(EditAnywhere, Category = "Ship | VFX")
	TSubclassOf<AActor> DeathParticle;

public:
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "Ship")
	void SetUpThrusters();

	// Virtual functions inherited from ISelectable
	virtual void OnSelect() override;
	
	virtual void OnDeselect() override;
	
	virtual EAllegiance GetAllegiance() override;
	
	virtual void SetAllegiance(EAllegiance pAllegiance) override;
	
	virtual FSelectableData GetSelectableData() override;
	
	virtual void IssueOrder(EOrders pOrder) override;
	
protected:
	UFUNCTION(BlueprintCallable, Category = "Ship")
	void ReceiveDamage(float pDamage);

	UFUNCTION()
	virtual void ManageDeath();

private:
	UFUNCTION()
	void CreateOrders();

	UFUNCTION()
	void CreateAbilities();

	UFUNCTION()
	void ManageThrusters();
	
	virtual TArray<TScriptInterface<IActivatable>> GetAllActivatables() override;
	
};
