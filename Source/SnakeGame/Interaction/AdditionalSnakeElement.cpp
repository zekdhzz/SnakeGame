// SnakeGame


#include "AdditionalSnakeElement.h"

#include "SnakeGame/Snake/SnakeBase.h"

AAdditionalSnakeElement::AAdditionalSnakeElement()
{
}

void AAdditionalSnakeElement::BeginPlay()
{
	Super::BeginPlay();
}

void AAdditionalSnakeElement::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AAdditionalSnakeElement::Interact(AActor* Interactor, bool bIsHead)
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

void AAdditionalSnakeElement::ApplyBuff(ASnakeBase* Snake)
{
	Snake->AddSnakeElement(true);
	this->Destroy();
}
