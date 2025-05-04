// Fill out your copyright notice in the Description page of Project Settings.


#include "LevelSpawner.h"
#include "MapData.h"

void ALevelSpawner::BeginPlay()
{
	FRotator Rotation = FRotator();
	for (int y = 0; y < MAPY; y++) {
		for (int x = 0; x < MAPX; x++) {
			if (MAP[y][x] == '#') {
				FVector Location = GetPointLocation(FIntVector2(x,y));
				GetWorld()->SpawnActor<AActor>(Block, Location, Rotation);
			}
		}
	}
}
