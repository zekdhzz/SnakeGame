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
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	AAdditionalSnakeElement();
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
	virtual void Interact(AActor* Interactor, bool bIsHead) override;
	
	virtual void ApplyBuff(ASnakeBase* Snake) override;
};
