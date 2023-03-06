// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

/**
 * 
 */
class IntroductionPageInfoStruct
{
public:
	IntroductionPageInfoStruct();
	~IntroductionPageInfoStruct();

	struct IntroductionPageInfo {

		int PageNum;

		FString SetText;

		FString ImagePath;
	};
};
