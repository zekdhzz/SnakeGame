// SnakeGame.


#include "PlayerPawnBase.h"
#include "Engine/Classes/Camera/CameraComponent.h"
#include "Components/InputComponent.h"
#include "SnakeGame/Snake/SnakeBase.h"
#include "SnakeGame/UI/StatHUD.h"
#include "Blueprint/UserWidget.h"
#include "SnakeGame/Interaction/Spawner.h"

// Sets default values
APlayerPawnBase::APlayerPawnBase()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	PawnCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("PawnCamera"));
	RootComponent = PawnCamera;

	PlayerHUD = nullptr;
	PlayerHUDClass = nullptr;
	
	InitHealth = 3;
}

// Called when the game starts or when spawned
void APlayerPawnBase::BeginPlay()
{
	Super::BeginPlay();
	SetActorRotation(FRotator(-90, 0, 0));
	SetHUD();
	CreateSpawner();
	SpawnInteractableActor();
	CreateSnakeActor();
}

void APlayerPawnBase::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	if (PlayerHUD)
	{
		PlayerHUD->RemoveFromParent();
		PlayerHUD = nullptr;
	}

	Super::EndPlay(EndPlayReason);
}

// Called every frame
void APlayerPawnBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void APlayerPawnBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("Vertical", this, &APlayerPawnBase::HandlePlayerVerticalInput);
	PlayerInputComponent->BindAxis("Horizontal", this, &APlayerPawnBase::HandlePlayerHorizontalInput);
}

void APlayerPawnBase::CreateSnakeActor()
{
	SnakeActor = GetWorld()->SpawnActor<ASnakeBase>(SnakeActorClass, FTransform());
	UpdateHealth(InitHealth);
}

void APlayerPawnBase::SetHUD()
{
	if (IsLocallyControlled() && PlayerHUDClass)
	{
		APlayerController* FPC = GetController<APlayerController>();
		if (FPC)
		{
			PlayerHUD = CreateWidget<UStatHUD>(FPC, PlayerHUDClass);
			if (PlayerHUD)
			{
				PlayerHUD->AddToPlayerScreen();
			}
		}
	}
}

void APlayerPawnBase::UpdateHealth(int32 Amount)
{
	CurrentHealth += Amount;
	PlayerHUD->SetHealth(CurrentHealth);
}

void APlayerPawnBase::UpdateSnakeSize(int32 Amount)
{
	CurrentSnakeSize += Amount;
	PlayerHUD->SetSnakeSize(CurrentSnakeSize);
}

void APlayerPawnBase::UpdatePointsCount(int32 Amount)
{
	CurrentPoints += Amount;
	PlayerHUD->SetPoints(CurrentPoints);
}

void APlayerPawnBase::HandlePlayerVerticalInput(float value)
{
	if (IsValid(SnakeActor))
	{
		if (value > 0 && SnakeActor->LastMovementDirection != EMovementDirection::DOWN)
		{
			SnakeActor->LastMovementDirection = EMovementDirection::UP;
		}
		else if (value < 0 && SnakeActor->LastMovementDirection != EMovementDirection::UP)
		{
			SnakeActor->LastMovementDirection = EMovementDirection::DOWN;
		}
	}
}

void APlayerPawnBase::HandlePlayerHorizontalInput(float value)
{
	if (IsValid(SnakeActor))
	{
		if (value > 0 && SnakeActor->LastMovementDirection != EMovementDirection::LEFT)
		{
			SnakeActor->LastMovementDirection = EMovementDirection::RIGHT;
		}
		else if (value < 0 && SnakeActor->LastMovementDirection != EMovementDirection::RIGHT)
		{
			SnakeActor->LastMovementDirection = EMovementDirection::LEFT;
		}
	}
}

void APlayerPawnBase::CreateSpawner()
{
	Spawner = GetWorld()->SpawnActor<ASpawner>(ASpawner::StaticClass(), FTransform());
}

void APlayerPawnBase::SpawnInteractableActor()
{
	Spawner->SpawnFood();
}
