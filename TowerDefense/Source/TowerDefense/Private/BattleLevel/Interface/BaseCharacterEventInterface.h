// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "BaseCharacterEventInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UBaseCharacterEventInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class IBaseCharacterEventInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:

	virtual void RequestDeleteCharacter(ACharacter* character) = 0;
	virtual void  RequestSerchEnemy(AActor* actor) = 0;
};
