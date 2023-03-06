// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "BaseMainWidget.h"
#include "WidgetManagerEventInterface.h"
#include "BaseMainWidgetManager.generated.h"

/**
 * 
 */
UCLASS()
class ABaseMainWidgetManager : public AHUD, public IWidgetManagerEventInterface
{
	GENERATED_BODY()


public:

	//Widget画面を開く
	virtual void OpenWidget() override;
	//Widget画面を閉じる
	virtual void CloseWidget() override;

protected:

	UBaseMainWidget* BaseMainWidgetPtr;
};
