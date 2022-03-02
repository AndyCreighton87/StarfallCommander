#include "HealthComponent.h"

#include "HealthBarWidget.h"
#include "StarfallCamera.h"
#include "StarfallGameMode.h"
#include "StarfallGameState.h"

UHealthComponent::UHealthComponent()
{
}

// Called when the game starts or when spawned
void UHealthComponent::BeginPlay()
{
	Super::BeginPlay();

	// Set Timer
	MaxHealth = CurrentHealth;
	TimeToDisplayOnHit = 5.0f;
	
	TimerDelegate.BindLambda([this]
	{
		if (this || !IsPendingKill())
			HideHealthBar();
	});
}

void UHealthComponent::TickComponent(float DeltaTime, ELevelTick Tick, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, Tick, ThisTickFunction);

	// Rotate towards the camera
	SetWorldRotation(TowardsCamera);
}

// Reduces health by parameter
void UHealthComponent::ReduceHealth(float pHealth)
{
	CurrentHealth -= pHealth;
	UpdateHealthBar();
	ManageHealthBarDisplay();
	CheckIsDead();
}

// Increase health by parameter
// This function is currently not used but allows for the idea of health pickups or
// healing
void UHealthComponent::IncreaseHealth(float pHealth)
{
	CurrentHealth += pHealth;
	UpdateHealthBar();
	ManageHealthBarDisplay();
}

// Broadcasts the OnDeath delegate if health is completely depleted
void UHealthComponent::CheckIsDead() const
{
	if (CurrentHealth <= 0)
	{
		GetWorld()->GetTimerManager().ClearAllTimersForObject(this);
		OnDeathDelegate.Broadcast();
	}
}

// Displays the timer. Starts the timer, once the timer expires hides the health bar.
// The timer can be reset.
void UHealthComponent::ManageHealthBarDisplay()
{
	ShowHealthBar();
	
	if (GetWorld()->GetTimerManager().TimerExists(TimerHandle))
		GetWorld()->GetTimerManager().ClearTimer(TimerHandle);

	GetWorld()->GetTimerManager().SetTimer(TimerHandle, TimerDelegate, TimeToDisplayOnHit, true);
}

void UHealthComponent::ShowHealthBar()
{
	SetVisibility(true);
}

void UHealthComponent::HideHealthBar()
{
	//if (this || !IsPendingKill())
	//	SetVisibility(false);
}

// Update the health bar widget
void UHealthComponent::UpdateHealthBar()
{
	const float tHealthPercentage = CurrentHealth / MaxHealth;
	UHealthBarWidget* tHealthBar = Cast<UHealthBarWidget>(Widget);
	
	if (tHealthBar)
		tHealthBar->UpdateHealthBar(tHealthPercentage);
}

