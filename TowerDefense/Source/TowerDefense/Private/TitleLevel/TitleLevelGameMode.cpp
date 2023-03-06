// Fill out your copyright notice in the Description page of Project Settings.


#include "TitleLevel/TitleLevelGameMode.h"
#include "Kismet/GamePlayStatics.h"
#include "../../Public/TowerDefenseGameInstance.h"




ATitleLevelGameMode::ATitleLevelGameMode() {

	HUDClass = ATitleLevelMainWidgetManager::StaticClass();
	PlayerControllerClass = ATitleLevelController::StaticClass();
	DefaultPawnClass = nullptr;
	NextCameraIndex = kFirstIndex;
	ChangeTime = kInitializeChangeTime;
	PrimaryActorTick.bCanEverTick = true;


}

void ATitleLevelGameMode::Tick(float DeltaTime){
	Super::Tick(DeltaTime);

	CountTime += DeltaTime;

	if (NextCameraIndex <= kLastCameraIndex) {

		if (CountTime >= ChangeTime) {

			TitleLevelControllerPtr->SetViewTargetWithBlend(CameraArray[NextCameraIndex], ChangeTime);

			NextCameraIndex++;

			ChangeTime += kPlusTime;

			CountTime = kResetTime;
		}
	}
}

void ATitleLevelGameMode::BeginPlay(){
	Super::BeginPlay();

	UTowerDefenseGameInstance* GameInstance = Cast<UTowerDefenseGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));

	if (IsValid(GameInstance)) {
	
	
		if (!GameInstance->GetbIsStartGameInstance()) {
		
		
			GameInstance->InitializeGameInstance();
		
		}
	
	}


	//BattleLevelControllerにキャスト
	TitleLevelControllerPtr = Cast<ATitleLevelController>(UGameplayStatics::GetPlayerController(this, 0));
	//キャストが成功すれば
	if (IsValid(TitleLevelControllerPtr)) {

		//HUDをBattleLevelWidgetManagerにキャストする
		TitleLevelWidgetManagerPtr = Cast<ATitleLevelMainWidgetManager>(TitleLevelControllerPtr->GetHUD());
		//キャストが成功すれば
		if (IsValid(TitleLevelWidgetManagerPtr)) {
			
			TitleLevelWidgetManagerPtr->InitializeMainWidgetManager();
			//キャストしたウィジェットマネージャに実装されたインターフェースをコントローラーに渡す
			TitleLevelControllerPtr->SetWidgetManagerEventInterface(TitleLevelWidgetManagerPtr);
			TitleLevelControllerPtr->SetTitleLevelControllerInterface(TitleLevelWidgetManagerPtr);


			//ウィジェットを開く
			TitleLevelControllerPtr->RequestOpenWidget();
			//マウスカーソルを出す
			TitleLevelControllerPtr->bShowMouseCursor = true;

			//カメラアクターがBattleLevelBPにセットされていれば、
			if (IsValid(FieldCamera)) {
				//そのカメラの視点を使う
				TitleLevelControllerPtr->SetViewTarget(FieldCamera);

				if (IsValid(FieldCamera2) && IsValid(FieldCamera3)) {
				
					CameraArray.Push(FieldCamera2);
					CameraArray.Push(FieldCamera3);
				
				}
			}

			TitleLevelWidgetManagerPtr->CallFadeInUI();

		}

	
	
	}
}
