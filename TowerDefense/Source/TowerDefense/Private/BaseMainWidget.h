// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "BaseMainWidget.generated.h"

/**
 * 
 */
UCLASS()
class UBaseMainWidget : public UUserWidget
{
	GENERATED_BODY()

public:

	//MainWidgetをヴューポートに追加する
	virtual void Open();

	//MainWidgetの終了処理。Widgetを閉じる
	virtual void Close();




	
};
