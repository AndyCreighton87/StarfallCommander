/// <summary>
/// The purpose of the Build Queue is to allow for creation of Ships. It implements
/// the abstract factory pattern to achieve this, however much of the functionality
/// is centered around allowing the player to queue up multiple items for creation.
/// Each ship takes a predetermined length of time to construct, the player can queue up to
/// 5 ships to different types. When a ship is added to the build queue the minerals are deducted
/// and population increased.
///
/// One of the main challenges faced with the Build Queue was the use of TQueue and communication
/// with the BuildQueueWidget. Despite being the perfect data structure for the job, the build queue
/// did not seem to work like other data structures. It could not utilize UPROPERTY, I could not iterate
/// through the queue, passing it as a parameter would result in compile errors and I generally had a hard
/// time getting any information stored within the queue out of this class. I have opted to replace the queue
/// with a TArray using random access to mock a queue. It works well but may look strange.
/// </summary>

#pragma once

#include "CoreMinimal.h"
#include "BuildableFactory.h"
#include "BulidableData.h"
#include "IBuilder.h"
#include "ResourceManager.h"
#include "BuildQueue.generated.h"

UCLASS()
class LJMUBASIC425_API ABuildQueue : public ABuildableFactory
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;

	virtual void Tick(float DeltaSeconds) override;
	
private:
	// Store a reference to the thing the owner of the build queue
	UPROPERTY()
	TScriptInterface<IBuilder> Builder;
	
	UPROPERTY(EditAnywhere, Category = "Build Queue")
	int BuildQueueMaxSize = 5;

	// The item currently being built
	UPROPERTY()
	FBuildableData ActiveItem;

	// I had initially tried to use a TQueue for the build queue, however this does not seem very well supported,
	// and I had a lot of issues performing simple operations such as passing it as a parameters, iterating through
	// it and even getting the number of elements. In the end I opted to use a TArray in place of it, and have created
	// a system where the Array acts like a Queue. 
	UPROPERTY()
	TArray<FBuildableData> BuildQueue;

	UPROPERTY()
	bool bIsBuilding = false;
	
	UPROPERTY()
	int32 BuildQueueCount = 0;

	UPROPERTY()
	AResourceManager* ResourceManager;

	// Timers
	FTimerHandle BuildQueueTimer;

	FTimerDelegate BuildQueueTimerDelegate;

	// Widget
	UPROPERTY()
	class UBuildQueueWidget* BuildQueueWidget;

public:
	UFUNCTION()
	void Init(TScriptInterface<IBuilder> pBuilder);
	
	UFUNCTION(BlueprintCallable)
	virtual TScriptInterface<IBuildable> CreateBuildable(FBuildableData PBuildable) override;

	UFUNCTION(BlueprintCallable)
	virtual bool AddToBuildQueue(FBuildableData pBuildable);

	UFUNCTION(BlueprintCallable)
	void RemoveFromBuildQueue();

	UFUNCTION()
	void StartBuildingItem(FBuildableData PBuildable);

	UFUNCTION(BlueprintCallable, Category = "Build Queue")
	void SetWidget(UUserWidget* pWidget);

	UFUNCTION(BlueprintCallable, Category = "Build Queue")
	void UpdateBuildQueueUI();

	UFUNCTION()
	void EmptyBuildQueue();
	
private:
	UFUNCTION()
	bool CheckResources(FBuildableData pBuildable) const;

	UFUNCTION()
	void OnFinishConstruction();
};
