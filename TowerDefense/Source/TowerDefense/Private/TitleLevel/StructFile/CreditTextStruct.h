// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Containers/UnrealString.h"
#include <string>

/**
 * 
 */
class CreditTextStruct
{
public:
	CreditTextStruct();
	~CreditTextStruct();

	struct CreditText {

		UPROPERTY()
		FString Title;

		UPROPERTY()
		FString URLString;
	};
};
