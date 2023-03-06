// Fill out your copyright notice in the Description page of Project Settings.


#include "BattleLevel/WidgetClass/IntroductionWidget.h"

void UIntroductionWidget::BindFunction(){

	
}

void UIntroductionWidget::SetAnimationIntoArray() {

	InAnimationArray.Push(InFirstPage);
	InAnimationArray.Push(InSecondPage);
	InAnimationArray.Push(InThirdPage);

	OutAnimationArray.Push(OutFirstPage);	
	OutAnimationArray.Push(OutSecondPage);
	OutAnimationArray.Push(OutThirdPage);
}

void UIntroductionWidget::SetPageContext() {

	TArray<UTextBlock*> TextBlockArray = { FirstText , SecondText, ThirdText };
	TArray<UImage*> ImageArray = { IntroductionImage, IntroductionImage2,IntroductionImage3 };

	for (int i = 0; i < PageInfoArray.Num(); i++) {
	
		FText Text = FText::FromString(PageInfoArray[i].SetText);

		TextBlockArray[i]->SetText(Text);
	
		TSoftObjectPtr<UTexture2D> ImageTexture = TSoftObjectPtr<UTexture2D>(FSoftObjectPath(*PageInfoArray[i].ImagePath));

		ImageArray[i]->SetBrushFromTexture(ImageTexture.LoadSynchronous());
	
	}
}

void UIntroductionWidget::SetIntroductionStringArray(TArray<FString> StringArray){


}

void UIntroductionWidget::SetText(int NowPage){

	
}

void UIntroductionWidget::Open(){

	UBaseMainWidget::Open();

	ShowFirstPage();
}

FReply UIntroductionWidget::NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent){

	UE_LOG(LogTemp, Log, TEXT("Call::NativeOnMouseButtonDown"));

	//TReplyBase< FReply >;
	NextPage();

	return FReply::Handled();
}

void UIntroductionWidget::ShowFirstPage() {

	PlayAnimation(InFirstPage, 0.0f, 1);

	NowPageIndex = 0;
}


void UIntroductionWidget::NextPage(){

	OutPage(NowPageIndex);

	NowPageIndex++;

	if (NowPageIndex >= InAnimationArray.Num()) {
	
		IntroductionInterface->RequestCloseIntroductionWidget();

		NowPageIndex = InAnimationArray.Num() - 1;
	}
	else {
		PlayAnimation(InAnimationArray[NowPageIndex], 0.0f, 1);

	}

}

void UIntroductionWidget::OutPage(int Index) {

	PlayAnimation(OutAnimationArray[Index], 0.0f, 1);
}


void UIntroductionWidget::BackPage()
{
}
