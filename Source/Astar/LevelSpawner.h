// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "LevelSpawner.generated.h"

/**
 * 
 */
UCLASS()
class ASTAR_API ALevelSpawner : public AGameModeBase
{
	GENERATED_BODY()
	

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	UClass* Block;


	void BeginPlay() override;
};
