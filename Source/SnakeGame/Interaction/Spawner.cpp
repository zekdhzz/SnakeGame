// SnakeGame


#include "Spawner.h"
#include "AdditionalHealth.h"
#include "Kismet/GameplayStatics.h"
#include "SnakeGame/Player/PlayerPawnBase.h"

// Sets default values
ASpawner::ASpawner()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SpawnParams.Owner = this;
	//SpawnParams.SpawnCollisionHandlingOverride =
	//	ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	SpawnParams.SpawnCollisionHandlingOverride =
		ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButDontSpawnIfColliding;

	CurrentPawn = Cast<APlayerPawnBase>(UGameplayStatics::GetPlayerPawn(this, 0));
	MinFoodCount = 3;
}

// Called when the game starts or when spawned
void ASpawner::BeginPlay()
{
	World = GEngine->GetWorldContextFromGameViewport(GEngine->GameViewport)->World();
	BPFoodList.Add("/Game/Blueprints/Interactable/BP_AdditionalSnakeElement.BP_AdditionalSnakeElement");
	BPFoodList.Add("/Game/Blueprints/Interactable/BP_AdditionalHealth.BP_AdditionalHealth");
	BPFoodList.Add("/Game/Blueprints/Interactable/Bp_SpeedUpSnake.Bp_SpeedUpSnake");

	Super::BeginPlay();
}

// Called every frame
void ASpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (SpawnedFoodList.Num() <= MinFoodCount)
	{
		SpawnFood();
	}
}

void ASpawner::SpawnFood()
{
	FString bp = BPFoodList[FMath::RandRange(0, 2)];
	UObject* SpawnActor = Cast<UObject>(StaticLoadObject(UObject::StaticClass(), nullptr, *bp));
	if (World)
	{
		auto Food = World->SpawnActor<AActor>(Cast<UBlueprint>(SpawnActor)->GeneratedClass,
		                                      FTransform(GenerateRandomCoordinatesInRange()), SpawnParams);
		SpawnedFoodList.Add(Cast<AFood>(Food));
	}
}

FVector ASpawner::GenerateRandomCoordinatesInRange()
{
	float X = FMath::RandRange(-700, 700);
	float Y = FMath::RandRange(-700, 700);
	return FVector(X, Y, 10);
}

void ASpawner::RemoveFromSpawnerList(AFood* Food)
{
	int32 count = SpawnedFoodList.Remove(Food);
	CurrentPawn->UpdatePointsCount(count);
}
