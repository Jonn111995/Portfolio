// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseMainWidgetManager.h"
#include "TitleLevelMainWidget.h"
//#include "CreditWidget.h"
//#include "Interface/CreditWidgetInterface.h"
//#include "Interface/TitleLevelMainWIdgetInterface.h"
#include "Interface/TitleLevelControllerInterface.h"
//#include "TitleLevelDataManager.h"
//#include "Widget/CreditScrollBox.h"
//#include "Widget/CreditTextBox.h"
#include "TitleLevelMainWidgetManager.generated.h"

/**
 * 
 */
UCLASS()
class ATitleLevelMainWidgetManager : public ABaseMainWidgetManager,/* public ITitleLevelMainWIdgetInterface, public ICreditWidgetInterface,*/ public ITitleLevelControllerInterface
{
	GENERATED_BODY()

public:

	/// <summary>
	/// 初期化関数
	/// </summary>
	void InitializeMainWidgetManager();

	void CallFadeInUI();

	/*virtual void RequestOpenCreditWidget() override;
	virtual void RequestOpenMainWidget() override;*/

	virtual void RequestMouseUp() override;
	virtual void RequestMouseDown() override;

private:

	UPROPERTY()
	TSubclassOf<UTitleLevelMainWidget> TitleLevelMainWidgetClass;

	UPROPERTY()
	UTitleLevelMainWidget* TitleLevelMainWidgetPtr;

	//UPROPERTY()
	//TSubclassOf<UCreditWidget> CreditWidgetClass;

	//UPROPERTY()
	//TSubclassOf<UCreditScrollBox> CreditScrollBoxWidgetClass;

	//UPROPERTY()
	//TSubclassOf<UCreditTextBox> CreditTextBoxWidgetClass;

	//
	//UPROPERTY()
	//UCreditWidget* CreditWidgetPtr;

	//UPROPERTY()
	//UCreditScrollBox* CreditScrollBoxWidgetPtr;

	//UPROPERTY()
	//UCreditTextBox* CreditTextBoxWidgetPtr;

	//UPROPERTY()
	//ATitleLevelDataManager* DataManager;

};
