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
	ACharacter* ControlCharacter;

	//UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	//FIntVector2 Position;

	void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

private:
	bool CanWalk(FIntVector2 pos);
	FIntVector2 NextPosition();

	
};
