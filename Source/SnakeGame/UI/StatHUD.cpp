// SnakeGame.


#include "StatHUD.h"
#include "Components/TextBlock.h"


void UStatHUD::NativeConstruct()
{
	Super::NativeConstruct();
}

void UStatHUD::SetHealth(const int32 Amount)
{
	HealthLabel->SetText(FText::AsNumber(Amount));
}

void UStatHUD::SetSnakeSize(int32 Amount)
{
	SnakeSizeLabel->SetText(FText::AsNumber(Amount));
}
