// SnakeGame.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "PlayerPawnBase.generated.h"

class ASpawner;
class UStatHUD;
class ASnakeBase;
class UCameraComponent;

UCLASS()
class SNAKEGAME_API APlayerPawnBase : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	APlayerPawnBase();

	UPROPERTY(BlueprintReadWrite)
	UCameraComponent* PawnCamera;

	UPROPERTY(BlueprintReadWrite)
	UStatHUD* PlayerHUD;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UStatHUD> PlayerHUDClass;

	UPROPERTY(BlueprintReadWrite)
	ASnakeBase* SnakeActor;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<ASnakeBase> SnakeActorClass;

	int32 InitHealth = 0;
	int32 CurrentHealth = 0;
	int32 CurrentSnakeSize = 0;
	int32 CurrentPoints = 0;

	UPROPERTY(EditDefaultsOnly)
	ASpawner* Spawner;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void CreateSnakeActor();

	void SetHUD();

	void UpdateHealth(int32 Amount);

	void UpdateSnakeSize(int32 Amount);

	void UpdatePointsCount(int32 Amount);

	UFUNCTION()
	void HandlePlayerVerticalInput(float value);

	UFUNCTION()
	void HandlePlayerHorizontalInput(float value);

	void CreateSpawner();

	void SpawnInteractableActor();
};
