// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseMainWidget.h"
#include "Components/TextBlock.h"
#include "Components/Image.h"
#include "Components/CanvasPanel.h"
#include "Components/Button.h"
#include "../Interface/IntroductionWidgetInterface.h"
#include "../StructFile/IntroductionPageInfoStruct.h"
#include "IntroductionWidget.generated.h"

/**
 * 
 */
UCLASS()
class UIntroductionWidget : public UBaseMainWidget
{
	GENERATED_BODY()

public:

	/// <summary>
	/// 使用するアニメーションを配列に入れる
	/// </summary>
	void SetAnimationIntoArray();
	
	/// <summary>
	/// ボタンWidgetに結びつける関数をバインドする
	/// </summary>
	void BindFunction();

	void SetIntroductionInfoArray(TArray<IntroductionPageInfoStruct::IntroductionPageInfo> Array) { PageInfoArray = Array; };

	/// <summary>
	/// 使用する文を説明文の配列に入れる
	/// </summary>
	void SetIntroductionStringArray(TArray<FString> StringArray);

	/// <summary>
	/// 表示するテキストをセットする
	/// </summary>
	void SetText(int NowPage);

	void ShowFirstPage();

	void SetIIntroductionWidgetInterface(IIntroductionWidgetInterface* Interface) { IntroductionInterface = Interface; };

	void SetPageContext();

protected:

	virtual void Open() override;
	virtual FReply NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;

private:

	IIntroductionWidgetInterface* IntroductionInterface;

	TArray<IntroductionPageInfoStruct::IntroductionPageInfo> PageInfoArray;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* FirstText;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* SecondText;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* ThirdText;

	UPROPERTY(meta = (BindWidget))
	UImage* IntroductionImage;

	UPROPERTY(meta = (BindWidget))
	UImage* IntroductionImage2;

	UPROPERTY(meta = (BindWidget))
	UImage* IntroductionImage3;
	
	//UPROPERTY(meta = (BindWidget))
		//    UButton* CloseButton;

	//UPROPERTY(meta = (BindWidget))
		//    UButton* CloseButton;

	UPROPERTY(Transient, meta = (BindWidgetAnim))
	UWidgetAnimation* InFirstPage;

	UPROPERTY(Transient, meta = (BindWidgetAnim))
	UWidgetAnimation* OutFirstPage;

	UPROPERTY(Transient, meta = (BindWidgetAnim))
	UWidgetAnimation* InSecondPage;

	UPROPERTY(Transient, meta = (BindWidgetAnim))
	UWidgetAnimation* OutSecondPage;

	UPROPERTY(Transient, meta = (BindWidgetAnim))
	UWidgetAnimation* InThirdPage;

	UPROPERTY(Transient, meta = (BindWidgetAnim))
	UWidgetAnimation* OutThirdPage;

	UPROPERTY(Transient, meta = (BindWidgetAnim))
	TArray<UWidgetAnimation*> InAnimationArray;

	UPROPERTY(Transient, meta = (BindWidgetAnim))
	TArray<UWidgetAnimation*> OutAnimationArray;

	TArray<FString> IntroductionStringArray;

	TArray<FText> IntroductionTextArray;

	UFUNCTION()
	void NextPage();

	UFUNCTION()
	void BackPage();

	void OutPage(int Index);

	int NowPageIndex;
	
};
