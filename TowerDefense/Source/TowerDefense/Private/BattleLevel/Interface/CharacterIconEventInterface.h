// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "CharacterIconEventInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UCharacterIconEventInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class ICharacterIconEventInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:

	virtual void RequestLaunchCharacter(int TypeId, float NeedCost, int x, int y, int StartRange) = 0;
	virtual void RequestShowCharaStatus(float NeedCost, int Hp, int Attack, int Defense, int StopEnemyNum, float AttackSpanNum) = 0;
	virtual void RequestHideCharaStatus() =0;
};
