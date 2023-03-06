//// Fill out your copyright notice in the Description page of Project Settings.
//
//
//#include "TitleLevel/Widget/CreditScrollBox.h"
//#include "Components/VerticalBox.h"
//#include "Kismet/GamePlayStatics.h"
//#include "Blueprint/WidgetLayoutLibrary.h"
//#include "Components/VerticalBoxSlot.h"
//#include "Components/CanvasPanelSlot.h"
//#include "Components/SizeBoxSlot.h"
//#include "Components/SizeBox.h"
//
//
//
//
//
//
//
//float UCreditScrollBox::GetSetVerticalBoxYSize(){
//
//	if (IsValid(SetVerticalBox)) {
//	
//	}
//	return SetVerticalBox->GetDesiredSize().Y; //UWidgetLayoutLibrary::SlotAsCanvasSlot(VerticalSize)->GetDesired
//}
//
//void UCreditScrollBox::SetCreditTextBlockToVertical(UCreditTextBox* TextBox){
//
//	SetVerticalBox->AddChildToVerticalBox(TextBox);
//}
//
//float UCreditScrollBox::GetTextBlockYSize(){
//
//	float AllSize = 0.0f;
//
//	for (int i = 0; i < CreditTextBoxArray.Num(); i++) {
//
//		AllSize += CreditTextBoxArray[i]->GetDesiredSize().Y;
//	}
//
//	return  AllSize;
//}
//
//void UCreditScrollBox::RemoveTopText(int RemoveIndex){
//
//	SetVerticalBox->RemoveChildAt(RemoveIndex);
//}
//
//void UCreditScrollBox::AddTextToUnder(int AddInex){
//
//	SetVerticalBox->AddChildToVerticalBox(CreditTextBoxArray[AddInex]);
//}
//
//int UCreditScrollBox::SerchIndexNowTopText(){
//
//
//	return 0;
//}
//
//void UCreditScrollBox::RemoveUnderText(int RemoveIndex){
//
//	SetVerticalBox->RemoveChildAt(RemoveIndex);
//}
//
//void UCreditScrollBox::AddTextToTop(int AddIndex){
//
//	SetVerticalBox->InsertChildAt(0, CreditTextBoxArray[AddIndex]);
//}
