// SnakeGame


#include "SpeedUpSnake.h"

#include "Spawner.h"
#include "SnakeGame/Snake/SnakeBase.h"

ASpeedUpSnake::ASpeedUpSnake()
{
}

void ASpeedUpSnake::BeginPlay()
{
	Super::BeginPlay();
}

void ASpeedUpSnake::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ASpeedUpSnake::Interact(AActor* Interactor, bool bIsHead)
{
	if (bIsHead)
	{
		ASnakeBase* Snake = Cast<ASnakeBase>(Interactor);
		if(IsValid(Snake))
		{
			ApplyBuff(Snake);
		}
	}
}

void ASpeedUpSnake::ApplyBuff(ASnakeBase* Snake)
{
	Snake->ChangeSnakeSpeed(0.1f);
	Cast<ASpawner>(this->GetOwner())->RemoveFromSpawnerList(this);
	this->Destroy();
}
