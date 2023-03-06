//// Fill out your copyright notice in the Description page of Project Settings.
//
//#pragma once
//
//#include "CoreMinimal.h"
//#include "Blueprint/UserWidget.h"
//#include "Components/VerticalBox.h"
//#include "Components/TextBlock.h"
//#include "CreditTextBox.h"
//#include "Components/CanvasPanel.h"
//#include "CreditScrollBox.generated.h"
//
///**
// * 
// */
//UCLASS()
//class UCreditScrollBox : public UUserWidget{
//
//	GENERATED_BODY()
//
//public:
//
//	UPROPERTY(meta = (BindWidget))
//	UVerticalBox* SetVerticalBox;
//
//	/*UPROPERTY(meta = (BindWidget))
//	USizeBox* VerticalSize;*/
//
//	UPROPERTY(meta = (BindWidget))
//	UCanvasPanel* SetCanvas;
//
//	float GetSetVerticalBoxYSize();
//
//	void SetCreditTextBlockToVertical(UCreditTextBox* TextBox);
//
//	float GetTextBlockYSize();
//
//	void SetCreditTextBoxArray(TArray<UCreditTextBox*> Array) { CreditTextBoxArray = Array; };
//
//	void RemoveTopText(int RemoveIndex);
//
//	void AddTextToUnder(int AddIndex);
//
//	int SerchIndexNowTopText();
//
//	void RemoveUnderText(int RemoveIndex);
//
//	void AddTextToTop(int AddIndex);
//	
//private:
//	UPROPERTY()
//		TArray<UCreditTextBox*> CreditTextBoxArray;
//};
