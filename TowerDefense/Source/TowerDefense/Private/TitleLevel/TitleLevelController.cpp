// Fill out your copyright notice in the Description page of Project Settings.


#include "TitleLevel/TitleLevelController.h"

void ATitleLevelController::SetupInputComponent(){

	Super::SetupInputComponent();

	check(InputComponent);

	if (IsValid(InputComponent)) {

		//クリックの動作と、マップにキャラをスポーンする処理を呼び出す関数をバインドする
		InputComponent->BindAction("MouseUp", IE_Pressed, this, &ATitleLevelController::MouseUp);
		InputComponent->BindAction("MouseDown", IE_Pressed, this, &ATitleLevelController::MouseDown);
	}

}

void ATitleLevelController::MouseUp(){
	TitleLevelControllerInterface->RequestMouseUp();
}

void ATitleLevelController::MouseDown(){

	TitleLevelControllerInterface->RequestMouseDown();
}
