// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseMainWidgetManager.h"

//Widget画面を開く
void ABaseMainWidgetManager::OpenWidget() {

	if (IsValid(BaseMainWidgetPtr)) {
	
		BaseMainWidgetPtr->Open();
	}

}


//Widget画面を閉じる
void ABaseMainWidgetManager::CloseWidget() {
	if (IsValid(BaseMainWidgetPtr)) {

		BaseMainWidgetPtr->Close();

	}
}