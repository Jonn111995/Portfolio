// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "WidgetManagerEventInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UWidgetManagerEventInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class IWidgetManagerEventInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:

	/// <summary>
	/// MainWidgetを開く
	/// </summary>
	virtual	void OpenWidget() = 0;
	/// <summary>
	/// MainWidgetを閉じる
	/// </summary>
	virtual	void CloseWidget() = 0;

};
