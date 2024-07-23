#include "GridCell.h"
#include "Components/TextRenderComponent.h"

// Sets default values
AGridCell::AGridCell()
{
	// Set this actor to call Tick() every frame. You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;


	//Assuming you have a static mesh component named "CellMesh"
	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("CellMesh"));
	RootComponent = StaticMeshComponent;

	MineText = CreateDefaultSubobject<UTextRenderComponent>(TEXT("MineText"));
	MineText->SetupAttachment(RootComponent);
	MineText->SetRelativeLocation(FVector(-60.f, -30.0f, -5.0f));
	MineText->SetRelativeRotation(FRotator(90.f, 180.f, 0.f));
	MineText->SetXScale(5.0f);
	MineText->SetYScale(5.0f);
	MineText->SetText(FText::FromString("0"));

	bIsRevealed = false;
	NeighborCount = 0;
}

// Called when the game starts or when spawned
void AGridCell::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AGridCell::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}


void AGridCell::OnHoverStart()
{
	FVector NewLocation = GetActorLocation();
	NewLocation.Z += 50.0f; // Elevate by 20 units
	StaticMeshComponent->SetMaterial(0, HoveredCell);
	SetActorLocation(NewLocation);
}

void AGridCell::OnHoverEnd()
{
	FVector NewLocation = GetActorLocation();
	NewLocation.Z -= 50.0f; // Return to original position
	StaticMeshComponent->SetMaterial(0, DefaultCell);
	SetActorLocation(NewLocation);
}

void AGridCell::Reveal()
{
	if (bIsRevealed) return; // Prevent revealing already revealed cells

	bIsRevealed = true;

	if (bIsBomb)
	{
		MineText->SetText(FText::FromString("B"));
		MineText->SetTextRenderColor(FColor::Orange);
	}
	else
	{
		MineText->SetText(FText::FromString(FString::FromInt(NeighborCount)));
		switch (NeighborCount)
		{
		case 1:
			MineText->SetTextRenderColor(FColor::White);
			break;
		case 2:
			MineText->SetTextRenderColor(FColor::Green);
			break;
		case 3:
			MineText->SetTextRenderColor(FColor::Red);
			break;
		case 4:
			MineText->SetTextRenderColor(FColor::Blue);
			break;
		case 5:
			MineText->SetTextRenderColor(FColor::Magenta);
			break;
		default:
			MineText->SetTextRenderColor(FColor::Turquoise);
			break;
		}
	}

	if (NeighborCount == 0)
	{
		FloodFill();
	}

	StaticMeshComponent->SetVisibility(!true);
}


void AGridCell::FloodFill()
{
	for (int32 i = -1; i <= 1; i++)
	{
		for (int32 j = -1; j <= 1; j++)
		{
			int32 NeighborRow = I + i;
			int32 NeighborCol = J + j;

			if (NeighborRow >= 0 && NeighborRow < GridArray.Num() &&
				NeighborCol >= 0 && NeighborCol < GridArray[NeighborRow].Num())
			{
				AGridCell* Neighbor = GridArray[NeighborRow][NeighborCol];
				if (Neighbor && !Neighbor->bIsRevealed)
				{
					Neighbor->Reveal();
				}
			}
		}
	}
}


int32 AGridCell::CountBombs()
{
	if (bIsBomb)
	{
		NeighborCount = -1;
		return -1;
	}

	int32 total = 0;

	for (int32 i = -1; i <= 1; i++)
	{
		for (int32 j = -1; j <= 1; j++)
		{

			int32 NeighborRow = I + i;
			int32 NeighborCol = J + j;

			// Check if the neighbor indices are within the bounds of the grid
			if (NeighborRow >= 0 && NeighborRow < GridArray.Num() &&
				NeighborCol >= 0 && NeighborCol < GridArray[NeighborRow].Num())
			{
				if (AGridCell* Neigh = GridArray[NeighborRow][NeighborCol])
				{
					if (Neigh->bIsBomb)
					{
						total++;
					}
				}
			}
		}
	}

	NeighborCount = total;

	// Update the visibility of the mine text
	MineText->SetText(FText::FromString(FString::FromInt(NeighborCount)));
	MineText->SetVisibility(NeighborCount > 0);

	return total;
}
