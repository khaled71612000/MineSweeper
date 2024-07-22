#include "MineSweeperPlayerController.h"
#include "MinesweeperGrid.h"
#include "../../../../../../../Source/Runtime/Engine/Public/EngineUtils.h"

// Sets default values
AMineSweeperPlayerController::AMineSweeperPlayerController()
{
	bShowMouseCursor = true;
	bCanClick = true;
	ClickCooldown = 1.f; // Cooldown period in seconds
	LastClickTime = 0.0f;
}

void AMineSweeperPlayerController::PlayerTick(float DeltaTime)
{
	Super::PlayerTick(DeltaTime);

	if (IsInputKeyDown(EKeys::LeftMouseButton) && bCanClick)
	{
		OnLeftMouseClick();
	}

	// Update cooldown timer
	if (!bCanClick)
	{
		LastClickTime += DeltaTime;
		if (LastClickTime >= ClickCooldown)
		{
			bCanClick = true;
			LastClickTime = 0.0f;
		}
	}
}

void AMineSweeperPlayerController::OnLeftMouseClick()
{
	bCanClick = false; // Disable further clicks until cooldown expires

	FVector WorldLocation, WorldDirection;

	if (DeprojectMousePositionToWorld(WorldLocation, WorldDirection))
	{
		FVector Start = WorldLocation;
		FVector End = WorldLocation + (WorldDirection * 10000.0f); // Adjust the length as needed

		for (TActorIterator<AMinesweeperGrid> It(GetWorld()); It; ++It)
		{
			AMinesweeperGrid* GridActor = *It;
			if (GridActor)
			{
				GridActor->LineTraceRevealCell(Start, End);
				break;
			}
		}
	}
}
