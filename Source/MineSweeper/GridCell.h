#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GridCell.generated.h"

UCLASS()
class MINESWEEPER_API AGridCell : public AActor
{
	GENERATED_BODY()
	
public:
	// Sets default values for this actor's properties
	AGridCell();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cell")
	class UStaticMeshComponent* StaticMeshComponent;

	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cell")
	//class UStaticMeshComponent* MineMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cell")
	class UTextRenderComponent* MineText;

	//void Initialize(int32 InI, int32 InJ, float InW);
	void Reveal();
	void FloodFill();
	int32 CountBombs();

	//bool Contains(float X, float Y) const;
	//void Show();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cell")
	int32 I;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cell")
	int32 J;

	TArray<TArray<AGridCell*>> GridArray;

	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cell")
	//float X;

	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cell")
	//float Y;

	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cell")
	//float W;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cell")
	int32 NeighborCount;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cell")
	bool bIsBomb;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cell")
	bool bIsRevealed;
};
