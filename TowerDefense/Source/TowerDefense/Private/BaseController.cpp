// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseController.h"

void ABaseController::RequestOpenWidget(){

	//ウィジェットを開くイベント通知を行う
	WIdgetManagerInterfacePtr->OpenWidget();
}

void ABaseController::RequestCloseWidget(){
	//ウィジェットを閉じるイベント通知を行う
	WIdgetManagerInterfacePtr->CloseWidget();
}

void ABaseController::SetWidgetManagerEventInterface(IWidgetManagerEventInterface* Interface) {

	WIdgetManagerInterfacePtr = Interface;
}
