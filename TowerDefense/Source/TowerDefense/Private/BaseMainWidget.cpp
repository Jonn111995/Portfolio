// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseMainWidget.h"

void UBaseMainWidget::Open(){
	//Widgetを追加
	AddToViewport();
}

void UBaseMainWidget::Close(){
	//Widgetを閉じる
	RemoveFromParent();
}
