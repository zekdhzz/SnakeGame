// SnakeGame


#include "AdditionalHealth.h"

#include "Spawner.h"
#include "SnakeGame/Snake/SnakeBase.h"

AAdditionalHealth::AAdditionalHealth()
{
}

void AAdditionalHealth::BeginPlay()
{
	Super::BeginPlay();
}

void AAdditionalHealth::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AAdditionalHealth::Interact(AActor* Interactor, bool bIsHead)
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

void AAdditionalHealth::ApplyBuff(ASnakeBase* Snake)
{
	Snake->AddHealthPoint();
	Cast<ASpawner>(this->GetOwner())->RemoveFromSpawnerList(this);
	this->Destroy();
}
