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
	CheckHover();

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

void AMineSweeperPlayerController::CheckHover()
{
	FVector WorldLocation, WorldDirection;

	if (DeprojectMousePositionToWorld(WorldLocation, WorldDirection))
	{
		FVector Start = WorldLocation;
		FVector End = WorldLocation + (WorldDirection * 10000.0f); // Adjust the length as needed

		FHitResult HitResult;
		FCollisionQueryParams Params;

		bool bHit = GetWorld()->LineTraceSingleByChannel(HitResult, Start, End, ECC_Visibility, Params);

		if (bHit && HitResult.GetActor())
		{
			AGridCell* HitCell = Cast<AGridCell>(HitResult.GetActor());
			if (HitCell && HitCell != LastHoveredCell)
			{
				if (LastHoveredCell)
				{
					LastHoveredCell->OnHoverEnd();
				}
				HitCell->OnHoverStart();
				LastHoveredCell = HitCell;
			}
		}
		else if (LastHoveredCell)
		{
			LastHoveredCell->OnHoverEnd();
			LastHoveredCell = nullptr;
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
