/// Custom component that manages health and displays it via the HealthWidget.
/// Features a timer that will display the health bar for a set period of time,
/// used when ships take damage.
#pragma once

#include "CoreMinimal.h"
#include "Components/WidgetComponent.h"
#include "GameFramework/Actor.h"
#include "HealthComponent.generated.h"

// Delegates
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnDeath);

UCLASS()
class LJMUBASIC425_API UHealthComponent : public UWidgetComponent
{
	GENERATED_BODY()
	
public:	
	UHealthComponent();

protected:
	virtual void BeginPlay() override;

	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

public:
	// Delegates
	UPROPERTY()
	FOnDeath OnDeathDelegate;

private:
	UPROPERTY(EditAnywhere, Category = "Health")
	float CurrentHealth;

	UPROPERTY()
	float MaxHealth;

	// Rotation towards the camera. I was trying to get this working at runtime,
	// directly from the StarfallCamera, however was running into trouble when doing so
	// This isn't great, but I manually entered the rotation and it works well.
	UPROPERTY()
	FRotator TowardsCamera = FRotator(50.0f, 180.0f, 0.0f);

	UPROPERTY()
	float TimeToDisplayOnHit;

	// Timers 
	FTimerHandle TimerHandle;

	FTimerDelegate TimerDelegate;
	
public:
	UFUNCTION(BlueprintCallable, Category = "Health")
	void ReduceHealth(float pHealth);

	UFUNCTION(BlueprintCallable, Category = "Health")
	void IncreaseHealth(float pHealth);

	UFUNCTION(BlueprintCallable, Category = "Health Bar")
	void UpdateHealthBar();

	UFUNCTION()
	void ShowHealthBar();

	UFUNCTION()
	void HideHealthBar();

private:
	UFUNCTION()
	void CheckIsDead() const;

	UFUNCTION()
	void ManageHealthBarDisplay();
};
