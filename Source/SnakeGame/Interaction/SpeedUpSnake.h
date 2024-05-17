// SnakeGame

#pragma once

#include "CoreMinimal.h"
#include "Food.h"
#include "SpeedUpSnake.generated.h"

/**
 * 
 */
UCLASS()
class SNAKEGAME_API ASpeedUpSnake : public AFood
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ASpeedUpSnake();
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
	virtual void Interact(AActor* Interactor, bool bIsHead) override;
	
	virtual void ApplyBuff(ASnakeBase* Snake) override;	
};
