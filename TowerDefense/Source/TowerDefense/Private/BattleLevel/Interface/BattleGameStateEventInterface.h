// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "BattleGameStateEventInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UBattleGameStateEventInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class IBattleGameStateEventInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:

	virtual void RequestDeletePlayerBaseActor(AActor* BaseActor) = 0;
	virtual void RequestGiveUpdateTime(float time) = 0;
	virtual void RequestGiveTickTimetToEnemySpawnerManager(float NowTime, float DeltaTime) = 0;
	virtual void RequestGameClear() = 0;
	virtual void RequestGameOver() = 0;
};
