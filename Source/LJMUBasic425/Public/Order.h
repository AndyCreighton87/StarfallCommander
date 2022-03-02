/// The Order class inherits from IActivatable. The idea behind an order is a set command
/// given to an AI agent, through the use of the behaviour tree the agent will then follow
/// the sequence of events until the order is completed.
///
/// Using the interface I created a polymorphic system that allows for many orders to be created
/// easily. The functionality of each order is handed within the behaviour tree, while the class
/// manages the state of the behaviour tree.

#pragma once

#include "CoreMinimal.h"
#include "EOrders.h"
#include "IActivatable.h"
#include "GameFramework/Actor.h"
#include "Order.generated.h"

UCLASS()
class LJMUBASIC425_API AOrder : public AActor, public IActivatable
{
	GENERATED_BODY()
	
public:	
	AOrder();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

public:
	// Struct containing all data for the order
	UPROPERTY(EditAnywhere, Category = "Order | Activitable Data")
	FActivitableData ActivitableData;

	// The button associated with order
	UPROPERTY()
	UButton* UIButton;

	// The ship that holds the order
	UPROPERTY(BlueprintReadWrite, Category = "Order")
	class ABaseShip* OwningShip;

private:
	// A flag that denotes if an order requires additional input after the orders button has been pressed
	// e.g. if the Move Order button is clicked, an additional click is required to inform the owning ship
	// where to move to. However, if the Stop order is pressed, it does not require any additional input,
	// the ship simply needs to stop. More on this in the OrderManager.
	UPROPERTY(EditAnywhere, Category = "Order")
	bool bRequiresInput;

	// Order manager reference
	UPROPERTY()
	class AOrderManager* OrderManager;

public:
	UFUNCTION()
	void Init(ABaseShip* pBaseShip);

	// Handed in blueprints
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "Order")
	void SetAIState();

	// Virtual functions from IActivatable
	virtual void OnActivate() override;
	
	virtual FActivitableData GetActivitableData() override;
	
	virtual FString GetName() override;
	
	virtual void BindToButton(UButton* pButton) override;
	
	virtual void RemoveBinding() override;

private:
	UFUNCTION()
	void AddToPending();

};
