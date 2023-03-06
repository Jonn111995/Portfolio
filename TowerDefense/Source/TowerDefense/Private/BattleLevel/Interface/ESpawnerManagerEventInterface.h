// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "../StructFile/EnemyBasePointStruct.h"
#include "ESpawnerManagerEventInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UESpawnerManagerEventInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class IESpawnerManagerEventInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:

	virtual TArray<EnemyBasePointStruct::EnemyBasePoint> RequestGetEnemyBasePosition() = 0;
};
