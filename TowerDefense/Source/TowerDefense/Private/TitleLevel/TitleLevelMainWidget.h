// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseMainWidget.h"
#include "Components/Button.h"
#include "Components/Image.h"
#include "Interface/TitleLevelMainWIdgetInterface.h"
#include "TitleLevelMainWidget.generated.h"

/**
 * 
 */
UCLASS()
class UTitleLevelMainWidget : public UBaseMainWidget
{
	GENERATED_BODY()

public:

	UPROPERTY(meta = (BindWidget))
	UButton* StartButton;

	//UPROPERTY(meta = (BindWidget))
	//UButton* CreditButton;

	UPROPERTY(Transient, meta = (BindWidgetAnim))
	UWidgetAnimation* FadeIn;

	UPROPERTY(Transient, meta = (BindWidgetAnim))
	UWidgetAnimation* FadeOut;


	UPROPERTY(Transient, meta = (BindWidgetAnim))
	UWidgetAnimation* FadeInUI;

	UFUNCTION()
	void OnStartButton();

	UFUNCTION()
    void OnCreditButton();

	void BindDelegateFunction();

	void SetTitleLevelMainWidgetInterface(ITitleLevelMainWIdgetInterface* Interface) { TitleLevelMainWidgetInterface = Interface; };

	virtual void Open() override;

	virtual void Close() override;

	void RequestFadeInUI();


private:
	ITitleLevelMainWIdgetInterface* TitleLevelMainWidgetInterface;
};
