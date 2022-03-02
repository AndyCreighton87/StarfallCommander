/// The Order Manager is responsible for storing orders that require additional
/// input (see Order.h). It will keep track of these orders until a second input has
/// been received at which point it will release them.
/// This was a class not originally in the design and was not a problem I had anticipated.
/// But I think the solution works well.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Info.h"
#include "OrderManager.generated.h"

UCLASS()
class LJMUBASIC425_API AOrderManager : public AInfo
{
	GENERATED_BODY()
	
public:	
	AOrderManager();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

private:
	// Orders awaiting execution
	UPROPERTY()
	TArray<class AOrder*> PendingOrders;

	// Flag to insure other orders can't be issued while in the process of
	// issuing an order
	UPROPERTY()
	bool bIsCurrentlyIssuingOrder = false;

public:
	UFUNCTION()
	void AddOrderToPending(AOrder* pOrder);

	UFUNCTION()
	void ExecutePendingOrders();

	UFUNCTION()
	void ClearPendingOrders();

	FORCEINLINE bool GetIsCurrentlyIssuingOrder() const { return bIsCurrentlyIssuingOrder; }
};
