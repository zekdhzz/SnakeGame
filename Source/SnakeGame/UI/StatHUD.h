// SnakeGame.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "StatHUD.generated.h"

class UTextBlock;
/**
 * 
 */
UCLASS(Abstract)
class SNAKEGAME_API UStatHUD : public UUserWidget
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	UTextBlock* HealthLabel;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	UTextBlock* SnakeSizeLabel;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	UTextBlock* PointsLabel;

	virtual void NativeConstruct() override;

public:
	void SetHealth(int32 Amount);
	void SetSnakeSize(int32 Amount);
	void SetPoints(int32 Amount);
};
