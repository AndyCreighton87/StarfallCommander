/// Capital Ship is the "base" of the game, it is the win/loss condition, while also houses a
/// build queue allowing it to produce additional units. All of the buildable data is stored within an
/// array of FBuildibleData structs, these structs hold a TSubClassOf ABaseShip.

#pragma once

#include "CoreMinimal.h"
#include "BulidableData.h"
#include "CombatShip.h"
#include "IBuilder.h"
#include "CapitalShip.generated.h"

UCLASS()
class LJMUBASIC425_API ACapitalShip : public ACombatShip, public IBuilder
{
	GENERATED_BODY()
	
public:
	ACapitalShip(const FObjectInitializer& ObjectInitializer);

protected:
	virtual void BeginPlay() override;
	
public:
	// Array of buildables - each ship able to be built is stored in here, edited through the details panel
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Buildable Ships")
	TArray<FBuildableData> Buildables;
	
protected:
	UPROPERTY()
	class ABuildQueue* BuildQueue;

	// Rally point - where the built ships will move when they are created.
	// I think a cool thing would have been to create an Order that allowed you to change the rally point
	// position. It would have be fairly straightforward to do within the existing framework, but it was low
	// priority and I ran out of time.
	UPROPERTY(EditAnywhere, Category = "Capital Ship")
	class USceneComponent* RallyPoint;

public:
	// IBuilder virtual functions
	virtual TArray<FBuildableData> GetBuildables() override;

	virtual ABuildQueue* GetBuildQueue() override;

	virtual FVector GetRallyPointPos() override;

	UFUNCTION()
	virtual void CleanUp();

protected:
	// Overridden function for use in child class
	virtual void ManageDeath() override;

private:
	UFUNCTION()
	void ClearBuildQueue() const;
};
