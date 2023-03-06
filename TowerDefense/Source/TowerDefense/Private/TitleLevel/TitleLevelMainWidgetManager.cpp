// Fill out your copyright notice in the Description page of Project Settings.


#include "TitleLevel/TitleLevelMainWidgetManager.h"
#include "Kismet/GameplayStatics.h"
#include "../../public/TowerDefenseGameInstance.h"

void ATitleLevelMainWidgetManager::InitializeMainWidgetManager() {

	//ゲームインスタンスを取得しキャスト
	UTowerDefenseGameInstance* GameInstance = Cast<UTowerDefenseGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));

	//キャストが成功していれば
	if (IsValid(GameInstance)) {
	
		//タイトルレベルのメインWIdgetのパスを取得
		FString Path = GameInstance->GetTitleLevelMainWidgetPath();
		//BPをロードする
		TitleLevelMainWidgetClass = TSoftClassPtr<UUserWidget>(FSoftObjectPath(*Path)).LoadSynchronous();
	
		////クレジット画面のパスを取得
		//Path = GameInstance->GetTitleLevelCreditWidgetPath();
		////BPをロードする
		//CreditWidgetClass = TSoftClassPtr<UUserWidget>(FSoftObjectPath(*Path)).LoadSynchronous();

		////クレジット画面のスクロールボックスWidgetのパスを取得
		//Path = GameInstance->GetTitleLevelCreditScrollBoxWidgetPath();
		////BPをロードする
		//CreditScrollBoxWidgetClass = TSoftClassPtr<UUserWidget>(FSoftObjectPath(*Path)).LoadSynchronous();

		////クレジット画面のテキストボックスWIdgetのパスを取得
		//Path = GameInstance->GetTitleLevelCreditTextBoxWidgetPath();
		////BPをロードする
		//CreditTextBoxWidgetClass = TSoftClassPtr<UUserWidget>(FSoftObjectPath(*Path)).LoadSynchronous();

		//TitleLevelMainWidgetClassが有効であれば、
		if (IsValid(TitleLevelMainWidgetClass)) {
		
			//MainWidgetを作る
			UUserWidget* Widget = CreateWidget(GetWorld(), TitleLevelMainWidgetClass);
			TitleLevelMainWidgetPtr = Cast<UTitleLevelMainWidget>(Widget);

			//TitleLevelMainWidgetPtr->SetTitleLevelMainWidgetInterface(this);

			TitleLevelMainWidgetPtr->BindDelegateFunction();

			BaseMainWidgetPtr = TitleLevelMainWidgetPtr;
		}

	//	//CreditScrollBoxWidgetClassが有効であれば、
	//	if (IsValid(CreditScrollBoxWidgetClass)) {

	//		UUserWidget* Widget = CreateWidget(GetWorld(), CreditScrollBoxWidgetClass);

	//		CreditScrollBoxWidgetPtr = Cast<UCreditScrollBox>(Widget);

	//	}

	//	//CreditWidgetClassが有効であれば、
	//	if (IsValid(CreditWidgetClass)) {

	//		UUserWidget* Widget = CreateWidget(GetWorld(), CreditWidgetClass);
	//		CreditWidgetPtr = Cast<UCreditWidget>(Widget);

	//		CreditWidgetPtr->SetCreditScrollBoxWidgetPtr(CreditScrollBoxWidgetPtr);

	//		CreditWidgetPtr->AddCreditScrollBoxWidgetToMain(CreditScrollBoxWidgetPtr);

	//		CreditWidgetPtr->SetCreditTextBoxWidgetClass(CreditTextBoxWidgetClass);

	//		CreditWidgetPtr->SetCreditWidgetInterface(this);

	//		CreditWidgetPtr->SetTitleLevelWorld(GetWorld());

	//		CreditWidgetPtr->BindDelegateFunction();
	//	}

	//	//TitleLevelDataManagerを生成する
	//	DataManager = NewObject<ATitleLevelDataManager>();

	//	//生成が成功していれば、
	//	if (IsValid(DataManager)) {
	//	
	//		DataManager->Initialize();

	//		CreditWidgetPtr->SetTextDataArray(DataManager->GetTextDataArray());
	//	
	//		CreditWidgetPtr->InitializeCreditWidget();
	//	}
	}
}

//void ATitleLevelMainWidgetManager::RequestOpenCreditWidget(){
//
//	CloseWidget();
//
//	BaseMainWidgetPtr = CreditWidgetPtr;
//
//	OpenWidget();
//}
//
//void ATitleLevelMainWidgetManager::RequestOpenMainWidget(){
//
//	CloseWidget();
//
//	BaseMainWidgetPtr = TitleLevelMainWidgetPtr;
//
//	OpenWidget();
//}

void ATitleLevelMainWidgetManager::RequestMouseUp(){

//	CreditWidgetPtr->CalculateGoUp();
}

void ATitleLevelMainWidgetManager::RequestMouseDown(){

	//CreditWidgetPtr->CalculateGoDown();
}

void ATitleLevelMainWidgetManager::CallFadeInUI(){

	TitleLevelMainWidgetPtr->RequestFadeInUI();
}
