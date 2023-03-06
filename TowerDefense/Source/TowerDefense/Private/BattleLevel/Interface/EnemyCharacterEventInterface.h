// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "EnemyCharacterEventInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UEnemyCharacterEventInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class IEnemyCharacterEventInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:

	virtual bool RequestCheckMapInfo(AActor* actor) = 0;
	virtual void RequestUpdatePtr(ACharacter* chara, const int x, const int y) = 0;
	virtual bool RequestCheckReachPlayerBase(ACharacter* chara) = 0;
	virtual void RequestReachPlayerBaseEvent(ACharacter* chara) = 0;
};
