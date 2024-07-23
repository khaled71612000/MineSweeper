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

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cell")
	class UTextRenderComponent* MineText;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cell")
	UMaterialInterface* RevealedCell;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cell")
	UMaterialInterface* HoveredCell;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cell")
	UMaterialInterface* DefaultCell;

	UFUNCTION()
	void OnHoverStart();

	UFUNCTION()
	void OnHoverEnd();

	void Reveal();
	void FloodFill();
	int32 CountBombs();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cell")
	int32 I;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cell")
	int32 J;

	TArray<TArray<AGridCell*>> GridArray;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cell")
	int32 NeighborCount;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cell")
	bool bIsBomb;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cell")
	bool bIsRevealed;
};
