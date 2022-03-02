/// Inherits from IActivatable and functions in a similar fashion to Order. I found a need to
/// have something that functions in a similar fashion to an order but does not rely on the
/// Behaviour Tree - it's not AI related. Unique Activatable fills that gap, it provides a lot
/// more flexibility.

#pragma once

#include "CoreMinimal.h"
#include "BaseShip.h"
#include "IActivatable.h"
#include "GameFramework/Actor.h"
#include "UniqueActivatable.generated.h"

UCLASS()
class LJMUBASIC425_API AUniqueActivatable : public AActor, public IActivatable
{
	GENERATED_BODY()
	
public:	
	AUniqueActivatable();

protected:
	virtual void BeginPlay() override;
	
public:	
	virtual void Tick(float DeltaTime) override;

public:
	// Struct storing information on activatable
	UPROPERTY(EditAnywhere, Category = "Ability | Activitable Data")
	FActivitableData ActivitableData;

private:
	// References
	UPROPERTY()
	UButton* UIButton;

	UPROPERTY()
	class ABaseShip* OwningShip;
	
public:
	UFUNCTION(BlueprintImplementableEvent, Category = "Unique")
	void Execute();

	UFUNCTION(BlueprintCallable, Category = "Unique")
	ABaseShip* GetOwningShip();

	UFUNCTION()
	void Init(ABaseShip* pBaseShip);

	// Virtual functions inherited from IActivatable
	virtual void OnActivate() override;

	virtual FActivitableData GetActivitableData() override;

	virtual FString GetName() override;

	virtual void BindToButton(UButton* pButton) override;

	virtual void RemoveBinding() override;

};
