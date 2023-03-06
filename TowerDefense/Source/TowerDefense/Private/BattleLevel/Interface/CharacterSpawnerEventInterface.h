// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "CharacterSpawnerEventInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UCharacterSpawnerEventInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class ICharacterSpawnerEventInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:

	virtual void RequestSetCharacterToPtrMap(ACharacter* chara) = 0;
	virtual void RequestCharacterPtrToNull(ACharacter* chara) = 0;
	virtual void RequestSetBaseCharaInterface(ACharacter* chara) = 0;
	virtual void RequestDecideCharaDirection(ACharacter& chara) = 0;

};
