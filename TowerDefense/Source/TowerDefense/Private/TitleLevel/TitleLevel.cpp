// Fill out your copyright notice in the Description page of Project Settings.


#include "TitleLevel/TitleLevel.h"
#include "Kismet/GamePlayStatics.h"
#include "Kismet/KismetSystemLibrary.h"

void ATitleLevel::PreInitializeComponents() {

	//ゲームモードを取得し、自作のゲームモードにキャストする
	TitleLevelGameModePtr = Cast<ATitleLevelGameMode>(UGameplayStatics::GetGameMode(GetWorld()));

	//キャストがされていれば
	if (IsValid(TitleLevelGameModePtr)) {


		//レベルBPにカメラが設定されていれば
		if (IsValid(FieldCamera)) {

			//ゲームモードにカメラのポインタを渡す。
			TitleLevelGameModePtr->SetFieldCamera(FieldCamera, FieldCamera2, FieldCamera3);
		}
	}

}

void ATitleLevel::BeginPlay(){

	UKismetSystemLibrary::ExecuteConsoleCommand(GetWorld(), "r.SetRes 1280x720w");
}
