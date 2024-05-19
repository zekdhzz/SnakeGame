// SnakeGame


#include "Spawner.h"
#include "AdditionalHealth.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "SnakeGame/Player/PlayerPawnBase.h"

// Sets default values
ASpawner::ASpawner()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SpawnParams.Owner = this;
	SpawnParams.SpawnCollisionHandlingOverride =
		ESpawnActorCollisionHandlingMethod::DontSpawnIfColliding;

	CurrentPawn = Cast<APlayerPawnBase>(UGameplayStatics::GetPlayerPawn(this, 0));
	MinFoodCount = 3;
	SetActorTickInterval(0.5f);
}

// Called when the game starts or when spawned
void ASpawner::BeginPlay()
{
	World = GEngine->GetWorldContextFromGameViewport(GEngine->GameViewport)->World();
	BPFoodList.Add("/Game/Blueprints/Interactable/BP_AdditionalSnakeElement.BP_AdditionalSnakeElement");
	BPFoodList.Add("/Game/Blueprints/Interactable/BP_AdditionalHealth.BP_AdditionalHealth");
	BPFoodList.Add("/Game/Blueprints/Interactable/Bp_SpeedUpSnake.Bp_SpeedUpSnake");
	MultipleSpawn();

	Super::BeginPlay();
}

// Called every frame
void ASpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ASpawner::SpawnFood()
{
	// UE_LOG(LogTemp, Error, TEXT("SpawnedFoodList lenth: %s"), *FString::Printf(TEXT("%d"), SpawnedFoodList.Num()));
	FString BPPath;
	if (UKismetMathLibrary::RandomBoolWithWeight(0.8f))
	{
		BPPath = BPFoodList[0];
	}
	else if (UKismetMathLibrary::RandomBoolWithWeight(0.1f))
	{
		BPPath = BPFoodList[1];
	}
	else
	{
		BPPath = BPFoodList[2];
	}
	//FString BPPath = BPFoodList[FMath::RandRange(0, 2)];
	UObject* SpawnActor = Cast<UObject>(StaticLoadObject(UObject::StaticClass(), nullptr, *BPPath));
	if (World)
	{
		auto Food = World->SpawnActor<AActor>(Cast<UBlueprint>(SpawnActor)->GeneratedClass,
		                                      FTransform(GenerateRandomCoordinatesInRange()), SpawnParams);
		if (Food)
		{
			SpawnedFoodList.Add(Cast<AFood>(Food));
		}
	}
}

FVector ASpawner::GenerateRandomCoordinatesInRange()
{
	return FVector(FMath::RandRange(-700, 700), FMath::RandRange(-700, 700), 10);
}

void ASpawner::RemoveFromSpawnerList(AFood* Food)
{
	CurrentPawn->UpdatePointsCount(SpawnedFoodList.Remove(Food));
	// UE_LOG(LogTemp, Error, TEXT("RemoveFromSpawnerList SpawnedFoodList lenth: %s"),
	//        *FString::Printf(TEXT("%d"), SpawnedFoodList.Num()));
	MultipleSpawn();
}

void ASpawner::MultipleSpawn()
{
	while (SpawnedFoodList.Num() < (MinFoodCount))
	{
		SpawnFood();
	}
}
