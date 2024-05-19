// SnakeGame

#pragma once

#include "CoreMinimal.h"
#include "Food.h"
#include "AdditionalSnakeElement.generated.h"

/**
 * 
 */
UCLASS()
class SNAKEGAME_API AAdditionalSnakeElement : public AFood
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AAdditionalSnakeElement();
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
	virtual void Interact(AActor* Interactor, bool bIsHead) override;
	
	virtual void ApplyBuff(ASnakeBase* Snake) override;
};
