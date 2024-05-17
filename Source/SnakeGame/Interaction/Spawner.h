// SnakeGame

#pragma once

#include "CoreMinimal.h"
#include "AdditionalSnakeElement.h"
#include "GameFramework/Actor.h"
#include "Spawner.generated.h"

class APlayerPawnBase;
class AFood;

UCLASS()
class SNAKEGAME_API ASpawner : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASpawner();
	
	UPROPERTY(EditDefaultsOnly)
	UWorld* World;
	
	FActorSpawnParameters SpawnParams;

	UPROPERTY()
	TArray<AFood*> SpawnedFoodList;

	UPROPERTY()
	int32 MinFoodCount;

	UPROPERTY()
	APlayerPawnBase* CurrentPawn;
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void SpawnFood();

	FVector GenerateRandomCoordinatesInRange();
	
	void RemoveFromSpawnerList(AFood* Food);
};
