// SnakeGame


#include "BlockBrick.h"
#include "SnakeGame/Snake/SnakeBase.h"
#include "SnakeGame/Snake/SnakeElementBase.h"

// Sets default values
ABlockBrick::ABlockBrick()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ABlockBrick::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ABlockBrick::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ABlockBrick::Interact(AActor* Interactor, bool bIsHead)
{
	auto Snake = Cast<ASnakeBase>(Interactor);
	if (IsValid(Snake))
	{
		for (auto SnakeElement : Snake->SnakeElements)
		{
			SnakeElement->Destroy();
		}
		Snake->Death();
	}
}

