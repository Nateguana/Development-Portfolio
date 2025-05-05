// Fill out your copyright notice in the Description page of Project Settings.


#include "AStarController.h"
#include "GameFramework\Character.h"
//#include "Navigation\PathFollowingComponent.h"

void AAStarController::BeginPlay()
{
	SetActorTickEnabled(true);
	//Possess((APawn*)ControlCharacter);
	UE_LOG(LogTemp, Warning, TEXT("Works"));
	////this->MoveToLocation
	Super::BeginPlay();
	Start = End = FIntVector2(14, 14);

	GoalObj = GetWorld()->SpawnActor<AActor>(Goal, FVector(), FRotator());
	SetRandomTarget();
	GenerateNextPosition();
}

void AAStarController::Tick(float DeltaTime)
{
	//UE_LOG(LogTemp, Warning, TEXT("Tick:%i"), GetMoveStatus());
	//Super::Tick(DeltaTime);
	ACharacter* character = GetCharacter();

	float mix = MixDiff / (float)InverseSpeed;

	FVector location = GetPointLocation(Start) * (1 - mix) + GetPointLocation(End) * mix;

	UE_LOG(LogTemp, Warning, TEXT("Target: %s; Start:%s; End:%s; Mixed:%s"), *Target.ToString(), *Start.ToString(), *End.ToString(), *location.ToString());

	character->SetActorLocation(location);

	MixDiff++;
	if (MixDiff == InverseSpeed) {
		if (End == Target) {
			SetRandomTarget();
		}
		GenerateNextPosition();
	}
}

bool AAStarController::CanWalk(bool Grid[MAPY][MAPX], FIntVector2& Pos)
{
	return Pos.X >= 0 && Pos.X < MAPX &&
		Pos.Y >= 0 && Pos.Y < MAPY &&
		MAP[Pos.Y][Pos.X] == '*' && !Grid[Pos.Y][Pos.X];

}

//https://forums.unrealengine.com/t/analogue-of-priority-queue/308540/2

struct PriorityType
{
	explicit PriorityType(FIntVector2 InPosition, FIntVector2 InOffset, int32 InPriority) {
		Position = InPosition;
		Priority = InPriority;
		FirstOffset = InOffset;
	}

	FIntVector2 FirstOffset;
	FIntVector2 Position;
	int32 Priority;
};

struct PriorityTypePredicate
{
	bool operator()(const PriorityType& A, const PriorityType& B) const
	{
		return A.Priority < B.Priority;
	}
};


FIntVector2 OFFSETS[4] = {
	FIntVector2(1,0),
	FIntVector2(0,1),
	FIntVector2(-1,0),
	FIntVector2(0,-1),
};

void AAStarController::GenerateNextPosition()
{
	bool grid[MAPY][MAPX];
	memset(grid, 0, sizeof(grid));

	Start = End;
	MixDiff = 0;

	grid[Start.Y][Start.X] = true;


	TArray<PriorityType> Queue;
	PriorityType Next(Start, FIntVector2::ZeroValue, 0);
	Queue.HeapPush(Next, PriorityTypePredicate());

	while (Queue.Num() > 0) {
		Queue.HeapPop(Next, PriorityTypePredicate(), EAllowShrinking::No);

		for (int j = 0; j < 4; j++) {
			FIntVector2 new_pos = Next.Position + OFFSETS[j];
			FIntVector2 new_offset = Next.Priority == 0 ? OFFSETS[j] : Next.FirstOffset;
			if (new_pos == Target) {
				End = Start + new_offset;
				return;
			}
			if (CanWalk(grid, new_pos)) {
				Queue.HeapPush(PriorityType(new_pos, new_offset, Next.Priority + 1), PriorityTypePredicate());
				grid[new_pos.Y][new_pos.X] = true;
			}
		}
	}

}

void AAStarController::SetRandomTarget()
{
	do {
		int y = FMath::RandRange(0, MAPY - 1);
		int x = FMath::RandRange(0, MAPX - 1);

		Target = FIntVector2(x, y);

	} while (MAP[Target.Y][Target.X] != '*');
	FVector Location = GetPointLocation(Target);
	GoalObj->SetActorLocation(Location);
}

//FIntVector2 AAStarController::NextPosition()
//{
//	return FIntVector2(1, 1);
//}
