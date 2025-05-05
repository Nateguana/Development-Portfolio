// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "MapData.h"
#include "AStarController.generated.h"

/**
 * 
 */
UCLASS()
class ASTAR_API AAStarController : public AAIController
{
	GENERATED_BODY()

public:

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	UClass* Goal;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	int InverseSpeed;

	//UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FIntVector2 Target;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	AActor* GoalObj;

	//UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	//FIntVector2 Position;

	void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

private:
	bool CanWalk(bool Grid[MAPY][MAPX], FIntVector2& Pos);
	void GenerateNextPosition();
	void SetRandomTarget();

	int MixDiff;
	FIntVector2 End;
	FIntVector2 Start;
	
};
