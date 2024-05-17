// SnakeGame

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Spawner.generated.h"

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
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void SpawnFood();

	FVector GenerateRandomCoordinatesInRange();
};
