// SnakeGame

#pragma once

#include "CoreMinimal.h"
#include "Food.h"
#include "AdditionalHealth.generated.h"

/**
 * 
 */
UCLASS()
class SNAKEGAME_API AAdditionalHealth : public AFood
{
	GENERATED_BODY()

public:	
	// Sets default values for this actor's properties
	AAdditionalHealth();
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
	virtual void Interact(AActor* Interactor, bool bIsHead) override;
	
	virtual void ApplyBuff(ASnakeBase* Snake) override;
	
};
