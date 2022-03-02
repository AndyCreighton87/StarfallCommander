/// Marks the location that Capital Ships will be spawned and the allegiance of those ships

#pragma once

#include "CoreMinimal.h"
#include "EAllegiance.h"
#include "GameFramework/Actor.h"
#include "PlayerStartLocation.generated.h"

UCLASS()
class LJMUBASIC425_API APlayerStartLocation : public AActor
{
	GENERATED_BODY()
	
public:	
	APlayerStartLocation(const FObjectInitializer& ObjectInitializer);

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Allegiance")
	EAllegiance Allegiance;

};
