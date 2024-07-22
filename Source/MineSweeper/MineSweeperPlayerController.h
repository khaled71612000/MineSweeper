#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "MineSweeperPlayerController.generated.h"

UCLASS()
class MINESWEEPER_API AMineSweeperPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	AMineSweeperPlayerController();

	virtual void PlayerTick(float DeltaTime) override;

private:
	void OnLeftMouseClick();

	bool bCanClick;
	float ClickCooldown;
	float LastClickTime;
};
