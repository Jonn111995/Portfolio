// Fill out your copyright notice in the Description page of Project Settings.


#include "TitleLevel/TitleLevelMainWidget.h"
#include "Kismet/GameplayStatics.h"

void UTitleLevelMainWidget::OnStartButton(){

	UGameplayStatics::OpenLevel(GetWorld(), "TowerDefenseLevel");
		UE_LOG(LogTemp, Log, TEXT("OnStart"));
}

void UTitleLevelMainWidget::OnCreditButton(){

	TitleLevelMainWidgetInterface->RequestOpenCreditWidget();

	UE_LOG(LogTemp, Log, TEXT("OnCredit"));
}

void UTitleLevelMainWidget::BindDelegateFunction(){

	StartButton->OnClicked.AddDynamic(this, &UTitleLevelMainWidget::OnStartButton);

	//CreditButton->OnClicked.AddDynamic(this, &UTitleLevelMainWidget::OnCreditButton);
}

void UTitleLevelMainWidget::Open(){
	PlayAnimation(FadeIn, 0.0f, 1);

	UBaseMainWidget::Open();
}

void UTitleLevelMainWidget::Close(){
	PlayAnimation(FadeOut, 0.0f, 1);

	UBaseMainWidget::Close();

}

void UTitleLevelMainWidget::RequestFadeInUI(){

	PlayAnimation(FadeInUI, 0.0f, 1);
}


