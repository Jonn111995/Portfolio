// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "TitleLevelControllerInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UTitleLevelControllerInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class ITitleLevelControllerInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:

	virtual void RequestMouseUp() = 0;
	virtual void RequestMouseDown() = 0;
};
