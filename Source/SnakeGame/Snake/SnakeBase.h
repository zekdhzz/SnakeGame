// SnakeGame.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Kismet/GameplayStatics.h"
#include "SnakeGame/UI/StatHUD.h"
#include "SnakeBase.generated.h"

class APlayerPawnBase;
class ASnakeElementBase;

UENUM()
enum class EMovementDirection
{
	UP,
	DOWN,
	LEFT,
	RIGHT
};

UCLASS()
class SNAKEGAME_API ASnakeBase : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ASnakeBase();
	
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<ASnakeElementBase> SnakeElementBase;

	UPROPERTY(EditDefaultsOnly)
	float ElementSize;

	UPROPERTY()
	TArray<ASnakeElementBase*> SnakeElements;

	UPROPERTY()
	EMovementDirection LastMovementDirection;

	UPROPERTY(EditDefaultsOnly)
	float MovementSpeed;

	UPROPERTY()
	APlayerPawnBase* CurrentPawn;

	int32 InitSnakeSize;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
	void AddSnakeElementInit(int ElementsCount = 1);
	
	void AddSnakeElement(bool bHiddenByDefault);
	
	void RevealIfHidden(TArray<ASnakeElementBase*>::ElementType CurrentElement);

	void Move();

	void Death();

	UFUNCTION()
	void SnakeElementOverlap(ASnakeElementBase* OverlappedElement, AActor* OtherActor);
};
