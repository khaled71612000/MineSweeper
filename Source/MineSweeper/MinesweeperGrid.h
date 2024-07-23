#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MinesweeperGrid.generated.h"

UCLASS()
class MINESWEEPER_API AMinesweeperGrid : public AActor
{
	GENERATED_BODY()
	
public:
	// Sets default values for this actor's properties
	AMinesweeperGrid();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;
	void LineTraceRevealCell(const FVector& Start, const FVector& End);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Grid")
	int32 Rows;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Grid")
	int32 Columns;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Grid")
	float CellSize;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Grid")
	TSubclassOf<class AGridCell> Cell;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Grid")
	int32 TotalBombs;

	UFUNCTION(BlueprintCallable, Category = "Grid")
	void InitializeGrid();

	void GameOver();

private:
	TArray<TArray<class AGridCell*>> GridArray;

	void CreateCell(int32 Row, int32 Column);
};
