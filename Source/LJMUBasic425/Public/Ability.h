
// The Ability class represents a Ship Ability. The idea would be that the player
// could activate a ship ability, it would increase a stat for a set duration e.g.
// attack speed. It would go onto cooldown, during which the player could not use it.
// Unfortunately, I was not able to get the feature into the game, and prioritised other
// systems. The framework for Activatables IS in the game (see Orders), it would have
// only been a case of managing the execution of the abilities.

// As it stands, when an ability button is clicked, the ability name will be shown
// through debug text. This is purely to show the Polymorphism at work, but there is
// zero functionality after the fact.

// There are no further comments in the .cpp of this class, a better demonstration of the
// system is found in the Order class.

#pragma once

#include "CoreMinimal.h"
#include "IActivatable.h"
#include "GameFramework/Actor.h"
#include "Ability.generated.h"

UCLASS()
class LJMUBASIC425_API AAbility : public AActor, public IActivatable
{
	GENERATED_BODY()
	
public:	
	AAbility();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ability | Parameters")
	float StatToChange;
	
private:
	UPROPERTY(EditAnywhere, Category = "Ability | Parameters")
	float Cooldown;

	UPROPERTY(EditAnywhere, Category = "Ability | Parameters")
	float Duration;

	UPROPERTY(EditAnywhere, Category = "Ability | Parameters", meta = (Clampmin = "0.0", ClampMax = "100.0"))
	float IncreaseAmount;

	UPROPERTY()
	bool IsOnCooldown;

	UPROPERTY()
	float ElapsedTime;

	UPROPERTY()
	class ABaseShip* OwningShip;

	UPROPERTY(EditAnywhere, Category = "Ability | Activitable Data")
	FActivitableData ActivitableData;

	UPROPERTY()
	UButton* UIButton;

	UPROPERTY()
	class AOrderManager* OrderManager;

public:
	UFUNCTION(BlueprintCallable, Category = "Ability")
	void Init(ABaseShip* pBaseShip);

	UFUNCTION(BlueprintCallable, Category = "Ability")
	bool GetIsOnCooldown();

	UFUNCTION(BlueprintCallable, Category = "Ability")
	ABaseShip* GetOwningShip();
	
	virtual void OnActivate() override;
	
	virtual FActivitableData GetActivitableData() override;
	
	virtual FString GetName() override;

	virtual void BindToButton(UButton* pButton) override;

	virtual void RemoveBinding() override;
};
