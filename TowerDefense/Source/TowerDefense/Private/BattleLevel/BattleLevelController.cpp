// Fill out your copyright notice in the Description page of Project Settings.


#include "BattleLevel/BattleLevelController.h"

ABattleLevelController::ABattleLevelController() {

	NowPhase = BattleLevelControllerPhase::Normal;
}

	//キーと関数をバインド
void ABattleLevelController::SetupInputComponent() {
	Super::SetupInputComponent();

	check(InputComponent);

	if (IsValid(InputComponent)) {
	
		//クリックの動作と、マップにキャラをスポーンする処理を呼び出す関数をバインドする
		InputComponent->BindAction("LaunchClick", IE_Pressed, this, &ABattleLevelController::OnClickMapChip);
	
	}

}


void ABattleLevelController::OnClickMapChip() {
	//クリックしたところにあるアクターの情報を受取る構造体
	FHitResult HitMapChip;
	TCHAR Tchar = 0;

	bool Check = false;
	switch (NowPhase) {

	//現在のフェーズが通常なら
	case Normal:

		UE_LOG(LogTemp, Log, TEXT("Call::Normal"));
		//クリックしたところにあるアクターの情報を取得し、
		GetHitResultUnderCursorByChannel(TraceTypeQuery1, false, HitMapChip);

		if (IsValid(HitMapChip.Actor.Get())){

			//キャラを撤退して、クリックするとなぜかクリックしていない方のキャラが消えている。
			//ゲームモードに撤退のイベント通知を行う
			Check = ControllerInterface->RequestRetreatPlayerCharacter(HitMapChip.Actor.Get());

			if (Check) {

				NowPhase = Normal;

					break;
			}

		}
	
		break;
	//キャラ配置フェーズなら
	case Arrange:

		//if (ReservedSpawnCharaTypeId != 0) {
			UE_LOG(LogTemp, Log, TEXT("Call::Arrange"));
			//クリックしたところにあるアクターの情報を取得し、
			GetHitResultUnderCursorByChannel(TraceTypeQuery1, true, HitMapChip);

			//ゲームモードにキャラスポーンのイベント通知を行う
			ControllerInterface->RequestSpawnCharacter(HitMapChip.Actor.Get(), ReservedSpawnCharaTypeId, ReservedNeedCost);
			break;

		//}

	case Wait:


		break;

	default:

		UE_LOG(LogTemp, Log, TEXT("Call::default"));

		break;

	};

}