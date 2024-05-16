// Fill out your copyright notice in the Description page of Project Settings.


#include "SnakeBase.h"
#include "SnakeElementBase.h"
#include "Interactable.h"

// Sets default values
ASnakeBase::ASnakeBase()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	ElementSize = 100.f;
	MovementSpeed = 10.f;
	LastMovementDirection = EMovementDirection::DOWN;
}

// Called when the game starts or when spawned
void ASnakeBase::BeginPlay()
{
	Super::BeginPlay();
	SetActorTickInterval(MovementSpeed);
	AddSnakeElementInit(5);
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

void ASnakeBase::AddSnakeElement(bool bHiddenByDefault)
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
}

void ASnakeBase::RevealIfHidden(TArray<ASnakeElementBase*>::ElementType CurrentElement)
{
	if (CurrentElement->MeshComponent->bHiddenInGame)
	{
		CurrentElement->MeshComponent->SetHiddenInGame(false);
	}
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
