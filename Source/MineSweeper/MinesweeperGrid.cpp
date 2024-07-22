#include "MinesweeperGrid.h"
#include "GridCell.h"
#include "Components/TextRenderComponent.h"

// Sets default values
AMinesweeperGrid::AMinesweeperGrid()
{
	// Set this actor to call Tick() every frame. You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Rows = 10;
	Columns = 10;
	CellSize = 100.0f;
}

// Called when the game starts or when spawned
void AMinesweeperGrid::BeginPlay()
{
	Super::BeginPlay();
	InitializeGrid();
}

// Called every frame
void AMinesweeperGrid::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AMinesweeperGrid::LineTraceRevealCell(const FVector& Start, const FVector& End)
{

	FHitResult HitResult;
	FCollisionQueryParams Params;

	bool bHit = GetWorld()->LineTraceSingleByChannel(HitResult, Start, End, ECC_Visibility, Params);

	if (bHit && HitResult.GetActor())
	{
		AGridCell* HitCell = Cast<AGridCell>(HitResult.GetActor());
		if (HitCell)
		{
			if (!HitCell->bIsBomb)
			{
				HitCell->Reveal();
			}
			else
			{
				GameOver();
			}
		}
	}

	// Optional: Draw debug line
	DrawDebugLine(GetWorld(), Start, End, FColor::Green, false, 1.0f, 0, 1.0f);
}
void AMinesweeperGrid::InitializeGrid()
{
	GridArray.SetNum(Rows);
	for (int32 Row = 0; Row < Rows; Row++)
	{
		GridArray[Row].SetNum(Columns);
		for (int32 Column = 0; Column < Columns; Column++)
		{
			CreateCell(Row, Column);
		}
	}

	TArray<FIntPoint> options;
	for (int32 i = 0; i < Columns; i++)
	{
		for (int32 j = 0; j < Rows; j++)
		{
			options.Add(FIntPoint(i, j));
		}
	}

	// Shuffle the list of all cell locations
	for (int32 i = GridArray.Num() - 1; i > 0; i--)
	{
		int32 j = FMath::RandRange(0, i);
		GridArray.Swap(i, j);
	}

	for (int32 n = 0; n < TotalBombs; n++)
	{
		int32 Index = FMath::RandRange(0, options.Num() - 1);
		FIntPoint Choice = options[Index];
		int32 i = Choice.X;
		int32 j = Choice.Y;
		options.RemoveAt(Index);
		GridArray[i][j]->bIsBomb = true;
		//GridArray[i][j]->MineMesh->SetStaticMesh(BombMesh);
		//GridArray[i][j]->MineText->SetVisibility(false);

		//FVector bombLocation = GridArray[i][j]->GetActorLocation();
		//bombLocation.Z -= 100;
		//AGridCell* NewCell = GetWorld()->SpawnActor<AGridCell>(Bomb, bombLocation, FRotator::ZeroRotator);

	}

	for (int32 i = 0; i < Columns; i++)
	{
		for (int32 j = 0; j < Rows; j++)
		{
			GridArray[i][j]->CountBombs();
		}
	}

}

void AMinesweeperGrid::GameOver()
{
	for (int32 i = 0; i < Columns; i++)
	{
		for (int32 j = 0; j < Rows; j++)
		{
			GridArray[i][j]->Reveal();
		}
	}
}

void AMinesweeperGrid::CreateCell(int32 Row, int32 Column)
{
	FVector Location(Row * CellSize, Column * CellSize, 0.0f);
	FRotator Rotation(0.0f, 0.0f, 0.0f);
	AGridCell* NewCell = GetWorld()->SpawnActor<AGridCell>(Cell, GetActorLocation() + Location, Rotation);
	GridArray[Row][Column] = (NewCell);
	NewCell->I = Row;
	NewCell->J = Column;
	NewCell->GridArray = GridArray;
}
