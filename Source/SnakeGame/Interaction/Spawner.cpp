// SnakeGame


#include "Spawner.h"
#include "AdditionalHealth.h"

// Sets default values
ASpawner::ASpawner()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	World = GEngine->GetWorldContextFromGameViewport(GEngine->GameViewport)->World();
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
	UObject* SpawnActor = Cast<UObject>(StaticLoadObject(UObject::StaticClass(), nullptr,
		TEXT("/Game/Blueprints/Interactable/BP_AdditionalSnakeElement.BP_AdditionalSnakeElement")));
	UBlueprint* GeneratedBP = Cast<UBlueprint>(SpawnActor);
	if (World)
	{
		FActorSpawnParameters SpawnParams;
		SpawnParams.Owner = this;
		SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButDontSpawnIfColliding;
		World->SpawnActor<AActor>(GeneratedBP->GeneratedClass, FTransform(FVector(20, 20, 0)), SpawnParams);
	}
}
