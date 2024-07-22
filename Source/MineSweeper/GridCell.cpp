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

	//MineMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("UnderMesh"));
	//MineMesh->SetupAttachment(RootComponent);
	//MineMesh->SetRelativeLocation(FVector(0.0f, 0.0f, -30.0f));
	//MineMesh->SetRelativeRotation(FRotator(90.f, 180.f, 0.f));
	//MineMesh->SetWorldScale3D(FVector(.6f));

	MineText = CreateDefaultSubobject<UTextRenderComponent>(TEXT("MineText"));
	MineText->SetupAttachment(RootComponent);
	MineText->SetRelativeLocation(FVector(-60.f, -30.0f, -10.0f));
	MineText->SetRelativeRotation(FRotator(90.f, 180.f, 0.f));
	MineText->SetXScale(3.0f);
	MineText->SetYScale(3.0f);
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


void AGridCell::Reveal()
{
	if (bIsBomb)
	{
		MineText->SetText(FText::FromString("xx"));
		//StaticMeshComponent
	}
	else
	{
		MineText->SetText(FText::FromString(FString::FromInt(NeighborCount)));
		//StaticMeshComponent
	}

	bIsRevealed = true;

	StaticMeshComponent->SetVisibility(!bIsRevealed);


	if (NeighborCount == 0)
	{
		FloodFill();
	}
}

void AGridCell::FloodFill()
{
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
					if (!Neigh->bIsBomb && !Neigh->bIsRevealed)
					{
						Neigh->Reveal();
					}
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


	if (NeighborCount <= 0)
	{
		MineText->SetVisibility(false);
	}
	else
	{
		MineText->SetVisibility(true);
	}

	return total;
}

//bool AGridCell::Contains(float X, float Y) const
//{
//	return false;
//}
//
//void AGridCell::Show()
//{
//
//}
