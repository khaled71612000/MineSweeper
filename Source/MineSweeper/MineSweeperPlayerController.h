#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "GridCell.h"
#include "MineSweeperPlayerController.generated.h"

UCLASS()
class MINESWEEPER_API AMineSweeperPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	AMineSweeperPlayerController();

	virtual void PlayerTick(float DeltaTime) override;
	void CheckHover();

	UPROPERTY()
	AGridCell* LastHoveredCell;
private:
	void OnLeftMouseClick();

	bool bCanClick;
	float ClickCooldown;
	float LastClickTime;
};
