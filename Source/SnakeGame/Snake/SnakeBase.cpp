// SnakeGame.


#include "SnakeBase.h"
#include "SnakeElementBase.h"
#include "SnakeGame/Player/PlayerPawnBase.h"
#include "SnakeGame/UI/StatHUD.h"

// Sets default values
ASnakeBase::ASnakeBase()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	ElementSize = 100.f;
	MovementSpeed = 10.f;
	LastMovementDirection = EMovementDirection::DOWN;
	CurrentPawn = Cast<APlayerPawnBase>(UGameplayStatics::GetPlayerPawn(this, 0));
	InitSnakeSize = 5;
}

// Called when the game starts or when spawned
void ASnakeBase::BeginPlay()
{
	SetActorTickInterval(MovementSpeed);
	AddSnakeElementInit(InitSnakeSize);
	Super::BeginPlay();
}

// Called every frame
void ASnakeBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	Move();
}

void ASnakeBase::AddSnakeElementInit(int ElementsCount)
{
	for (int i = 0; i < ElementsCount; ++i)
	{
		AddSnakeElement(false);
	}
}

void ASnakeBase::AddSnakeElement(bool bHiddenByDefault = true)
{
	FVector NewLocation(SnakeElements.Num() * ElementSize, 0, 0);
	FTransform NewTransform(NewLocation);
	ASnakeElementBase* NewSnakeElem = GetWorld()->SpawnActor<ASnakeElementBase>(SnakeElementBase, NewTransform);
	NewSnakeElem->SnakeOwner = this;
	int32 ElementIndex = SnakeElements.Add(NewSnakeElem);
	if (bHiddenByDefault)
	{
		NewSnakeElem->MeshComponent->SetHiddenInGame(true);
	}
	if (ElementIndex == 0)
	{
		NewSnakeElem->SetFirstElementType();
	}
	CurrentPawn->UpdateSnakeSize(1);
}

void ASnakeBase::RevealIfHidden(TArray<ASnakeElementBase*>::ElementType CurrentElement)
{
	if (CurrentElement->MeshComponent->bHiddenInGame)
	{
		CurrentElement->MeshComponent->SetHiddenInGame(false);
	}
}

void ASnakeBase::AddHealthPoint()
{
	CurrentPawn->UpdateHealth(1);
}

void ASnakeBase::ChangeSnakeSpeed(float Amount)
{
	MovementSpeed -= Amount;
	SetActorTickInterval(MovementSpeed);
}

void ASnakeBase::Move()
{
	FVector MovementVector(FVector::ZeroVector);

	switch (LastMovementDirection)
	{
	case EMovementDirection::UP:
		MovementVector.X += ElementSize;
		break;
	case EMovementDirection::DOWN:
		MovementVector.X -= ElementSize;
		break;
	case EMovementDirection::LEFT:
		MovementVector.Y += ElementSize;
		break;
	case EMovementDirection::RIGHT:
		MovementVector.Y -= ElementSize;
		break;
	}

	SnakeElements[0]->ToggleCollision();

	for (int i = SnakeElements.Num() - 1; i > 0; i--)
	{
		auto CurrentElement = SnakeElements[i];
		auto PrevElement = SnakeElements[i - 1];
		FVector PrevLocation = PrevElement->GetActorLocation();
		CurrentElement->SetActorLocation(PrevLocation);
		RevealIfHidden(CurrentElement);
	}

	SnakeElements[0]->AddActorWorldOffset(MovementVector);
	SnakeElements[0]->ToggleCollision();
}

void ASnakeBase::Death()
{
	CurrentPawn->UpdateHealth(-1);
	if (CurrentPawn->CurrentHealth)
	{
		Respawn();
	}
	Destroy();
}

void ASnakeBase::Respawn()
{
	CurrentPawn->UpdateSnakeSize(-CurrentPawn->CurrentSnakeSize);
	CurrentPawn->CreateSnakeActor();
}

void ASnakeBase::SnakeElementOverlap(ASnakeElementBase* OverlappedElement, AActor* OtherActor)
{
	if (IsValid(OverlappedElement))
	{
		int32 ElementIndex;
		SnakeElements.Find(OverlappedElement, ElementIndex);
		bool bIsFirst = ElementIndex == 0;
		IInteractable* InteractableInterface = Cast<IInteractable>(OtherActor);
		if (InteractableInterface)
		{
			InteractableInterface->Interact(this, bIsFirst);
		}
	}
}
