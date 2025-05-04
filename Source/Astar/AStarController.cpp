// Fill out your copyright notice in the Description page of Project Settings.


#include "AStarController.h"
#include "Navigation\PathFollowingComponent.h"

void AAStarController::BeginPlay()
{
	SetActorTickEnabled(true);
	//Possess((APawn*)ControlCharacter);
	UE_LOG(LogTemp, Warning, TEXT("Works"));
	////this->MoveToLocation
	Super::BeginPlay();
}

void AAStarController::Tick(float DeltaTime)
{
	UE_LOG(LogTemp, Warning, TEXT("Tick:%i"), GetMoveStatus());
	if (GetMoveStatus() == EPathFollowingStatus::Idle)
	{
		FIntVector2 NextPos = NextPosition();
		FVector NextLocation = FVector(100, 100, 50);//GetPointLocation(NextPos);
		UE_LOG(LogTemp, Warning, TEXT("Moving to: %s"), *NextLocation.ToString());
		auto val = this->MoveToLocation(NextLocation, 1.f);
		UE_LOG(LogTemp, Warning, TEXT("Res:%i"), val);
	}
}

FIntVector2 AAStarController::NextPosition()
{
	return FIntVector2(1, 1);
}
