// SnakeGame


#include "Spawner.h"
#include "AdditionalHealth.h"

// Sets default values
ASpawner::ASpawner()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	World = GEngine->GetWorldContextFromGameViewport(GEngine->GameViewport)->World();

	SpawnParams.Owner = this;
	//SpawnParams.SpawnCollisionHandlingOverride =
	//	ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	SpawnParams.SpawnCollisionHandlingOverride =
		ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButDontSpawnIfColliding;
}

// Called when the game starts or when spawned
void ASpawner::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ASpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ASpawner::SpawnFood()
{
	const TCHAR* BPName = TEXT("/Game/Blueprints/Interactable/BP_AdditionalSnakeElement.BP_AdditionalSnakeElement");
	UObject* SpawnActor = Cast<UObject>(StaticLoadObject(UObject::StaticClass(), nullptr,BPName));
	if (World)
	{
		World->SpawnActor<AActor>(Cast<UBlueprint>(SpawnActor)->GeneratedClass,
		                          FTransform(GenerateRandomCoordinatesInRange()), SpawnParams);
	}
}

FVector ASpawner::GenerateRandomCoordinatesInRange()
{
	int X = FMath::RandRange(-700, 700);
	int Y = FMath::RandRange(-700, 700);
	return FVector(X, Y, 10);
}
