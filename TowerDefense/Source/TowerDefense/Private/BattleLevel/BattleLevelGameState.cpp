// Fill out your copyright notice in the Description page of Project Settings.


#include "BattleLevel/BattleLevelGameState.h"

ABattleLevelGameState::ABattleLevelGameState() {

 PrimaryActorTick.bCanEverTick = true;

 NowPhase = kNone;

}


void ABattleLevelGameState::BeginPlay() {
	 Super::BeginPlay();
}

void ABattleLevelGameState::Tick(float DeltaTime) {
		
	Super::Tick(DeltaTime);
	//経過時間を入れるため初期化
	float PassedTime = 0.0f;

	switch (NowPhase) {

	case kTimer:
		//現在の時間から毎フレームの時間を引く
		NowTime = NowTime - DeltaTime;

		//残り時間が0であれば、
		if (NowTime <= kNoLeftLimitiTime) {
		
			//現在の時間を0にして、
			NowTime = kNoLeftLimitiTime;
			//クリアのフラグを立てる
			GameClear = true;
		
		}

		//開始から何秒たったかを計算
		PassedTime = LimitSeconds - NowTime;

		//経過時間と毎フレーム時間を渡して、スポーン処理を呼ぶ
		BattleGameStateInterface->RequestGiveTickTimetToEnemySpawnerManager(PassedTime, DeltaTime);
		//現在の時間をWidgetの方に渡すため、イベント通知
		BattleGameStateInterface->RequestGiveUpdateTime(NowTime);

		//ゲームクリアをしていれば、
		if (GameClear) {
			
			//クリアのイベント通知をする
			BattleGameStateInterface->RequestGameClear();
				
		}

		break;

	//終了フェーズ。なにもさせない
	case kFinish:

		break;
	}
}


void ABattleLevelGameState::DamageToBase(int damage, int x, int y){

	//味方拠点の配列を回す
	for (int i = 0; i < PlayerBaseArray.Num(); i++) {
	
		//味方拠点の座標を渡す
		int BaseX = PlayerBaseArray[i]->GetXPoint();
		int BaseY = PlayerBaseArray[i]->GetYPoint();

		//味方拠点の座標と引き数の敵の座標が一致すれば、
		if (BaseX == x && BaseY == y) {
		
			//拠点にダメージを与える
			bool IsDead = PlayerBaseArray[i]->GetDamage(damage);

			//拠点のHPが無くなったら。
			if (IsDead) {
			
				//ゲームマネージャ―に削除依頼を行う。
				BattleGameStateInterface->RequestDeletePlayerBaseActor(PlayerBaseArray[i]);
			
				//削除したアクターのポインタを削除
				PlayerBaseArray.RemoveAt(i);
			}

			//拠点が全滅すれば
			if (PlayerBaseArray.Num() == kAllBaseDestroy) {
				
				//ゲームオーバーのイベント通知を行う
				BattleGameStateInterface->RequestGameOver();
					
			}
		}
	}
}

void ABattleLevelGameState::StartTimer() {

	//現在の時間に制限時間を入れて初期化する
	NowTime = LimitSeconds;

}
