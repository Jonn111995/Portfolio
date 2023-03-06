// Fill out your copyright notice in the Description page of Project Settings.


#include "BattleLevel/BattleLevelGameMode.h"
#include "Kismet/GamePlayStatics.h"
#include "EnemyCharacter.h"
#include "../../Public/TowerDefenseGameInstance.h"



ABattleLevelGameMode::ABattleLevelGameMode() {

	HUDClass = ABattleLevelMainWidgetManager::StaticClass();
	PlayerControllerClass = ABattleLevelController::StaticClass();
	PlayerStateClass = ABattlePlayerState::StaticClass();
	DefaultPawnClass = nullptr;
	GameStateClass = ABattleLevelGameState::StaticClass();
	PrimaryActorTick.bCanEverTick = true;

	//float CountTime = 0.0f;
}

void ABattleLevelGameMode::SetBattleField(ABattleField* field) {
	
	Field = field;
}

void ABattleLevelGameMode::SetPlayerCharaSpawner(APlayerCharacterSpawner* spawner){

	PlayerCharaSpawnerPtr = spawner;
}


void ABattleLevelGameMode::SetFieldCamera(AActor* camera) {

	FieldCamera = camera;
}

bool ABattleLevelGameMode::RequestCheckCanArrange(FVector position) {

	//BattleFieldの指定した座標が置けるマスかどうかを確認する。
	bool bIsCanArrange = Field->CheckMapChip(position);

	//trueであればtrueを返す
	if (bIsCanArrange) {
	
		return true;
	}
	else {
	
		return false;
	}

	return false;
}

void ABattleLevelGameMode::RequestDecideCharaDirection(ACharacter& chara){

	//BaseCharacterにダウンキャスト
	//元々がPlayerCharacterクラスなので問題無し。
	ABaseCharacter* BaseChara = Cast<ABaseCharacter>(&chara);

	//座標を取り出す
	int x =BaseChara->GetXPoint();
	int y =BaseChara->GetYPoint();
	//マップの方角の変数を宣言し初期化
	ABattleField::FieldDirection Direction = ABattleField::FieldDirection::kNone;
	//座標と方角を渡す。
	//方角は参照渡ししているので、変更されたものが返ってくる
	Field->DecideDirectionCharacter(x,y,Direction);

	//返ってきた方角を確認
	switch (Direction) {
	
	//北なら
	case ABattleField::FieldDirection::kNorth:

		//キャラの向きを北に設定
		BaseChara->SetNowDirection(ABaseCharacter::CharacterDirection::kNorth);

		break;
	//南なら
	case ABattleField::FieldDirection::kSouth:
		//キャラの向きを南に設定
		BaseChara->SetNowDirection(ABaseCharacter::CharacterDirection::kSouth);

		break;
	//東なら
	case ABattleField::FieldDirection::kEast:
		//キャラの向きを東に設定
		BaseChara->SetNowDirection(ABaseCharacter::CharacterDirection::kEast);

		break;
	//西なら
	case ABattleField::FieldDirection::kWest:
		//キャラの向きを西に設定
		BaseChara->SetNowDirection(ABaseCharacter::CharacterDirection::kWest);

		break;
	}
}


void ABattleLevelGameMode::RequestChangePlayerControllerPhase(int TypeId, float NeedCost, int x, int y, int StartRange) {


	//BattlePlayerStateにコストがあるかを確認する
	bool IsCostExist = BattlePlayerState->CheckNowSpawnCost(NeedCost);
	
	if (IsCostExist) {

		//あれば処理を続行
		//アイコンウィジェットが押されたら、コントローラーのフェーズをキャラ配置フェーズにして、
		//クリックしたところにあるアクターの情報を取得する
		BattleLevelControllerPtr->SetPhase(ABattleLevelController::BattleLevelControllerPhase::Arrange);
		//ここまでに、スポーンさせる味方キャラのIDを引き数で持ってきて、コントローラーに予約する。
		BattleLevelControllerPtr->SetReservedSpawnCharaTypeId(TypeId);
		BattleLevelControllerPtr->SetReservedNeedCost(NeedCost);

		//選択中のUI表示を実行する
		BattleLevelWidgetManagerPtr->RequestSelectIn(TypeId);

		//ここでマップチップを光らせる処理。
		//索敵範囲をアイコンに持たせて、各マップチップにその範囲を持たせる。
		Field->RequestSetSpawnMapChipPhase(APlayerSpawnMapChip::SpawnMapChipPhase::kSelecting);
        Field->RequestSetSpawnMapChipShowRange(x, y, StartRange);
		//エフェクトを発生させる
		Field->RequestSpawnSelectingParticle();
	}
	else {
	
		//コストが足りない時はコストが足りないというメッセージを表示する
		BattleLevelWidgetManagerPtr->RequestShowSpawnMessage(TypeId, TEXT("コストが足りません"));
	}	
}

bool ABattleLevelGameMode::RequestSpawnCharacter(AActor* actor, int TypeId, float NeedCost){

	//引き数のアクターが有効であれば、
	if (IsValid(actor)) {

		//そのアクターがある座標に味方キャラクターをスポーンさせる
		//ここでいうアクターはクリックしたマップチップのこと
		bool IsSpawnSuccess = PlayerCharaSpawnerPtr->SpawnPlayerCharacter(TypeId, actor->GetActorLocation());

		if (IsSpawnSuccess) {

			//ここでコストを減らす処理をする。
			BattlePlayerState->SubtractCost(NeedCost);
			//更新したコストをWidgetの表示の方にも反映する
			BattleLevelWidgetManagerPtr->UpdateCost(BattlePlayerState->GetNowSpawnCost());

			//スポーン成功したことをメッセージとして出す
			BattleLevelWidgetManagerPtr->RequestShowSpawnMessage(TypeId, TEXT("出撃完了!!"));
			//キャラ選択中のUI表示を消す
			BattleLevelWidgetManagerPtr->RequestSelectOut(TypeId);

			//キャラの攻撃範囲を示すための表示を消す
			Field->CallResetColorMaterial();

			//スポーン地点に発生している選択中パーティクルエフェクトを消す
			Field->RequestOffSelectingParticle();

			//スポーン地点のフェーズをkSelectingからkNoneに変える
			Field->RequestSetSpawnMapChipPhase(APlayerSpawnMapChip::SpawnMapChipPhase::kNone);

			//コントローラーのフェーズをノーマルにする
			BattleLevelControllerPtr->SetPhase(ABattleLevelController::BattleLevelControllerPhase::Normal);
			return true;
		}
		else {
		
			//ここでもしキャラを置けなかったら置けないというメッセージを出す。
			BattleLevelWidgetManagerPtr->RequestShowSpawnMessage(TypeId, TEXT("スポーン地点をクリック！"));

			return false;
		
		}
		//コントローラーのフェーズをノーマルにする
		BattleLevelControllerPtr->SetPhase(ABattleLevelController::BattleLevelControllerPhase::Normal);
		return false;
	}
	else {
		//アクターが有効でなければ、コントローラーのフェーズをノーマルに戻すだけの処理を行う
		BattleLevelControllerPtr->SetPhase(ABattleLevelController::BattleLevelControllerPhase::Normal);

		//ここでもしキャラを置けなかったら置けないというメッセージを出す。
		BattleLevelWidgetManagerPtr->RequestShowSpawnMessage(TypeId, TEXT("Can Not Spawn!"));
		//キャラ選択中のＵＩ表示を消す
		BattleLevelWidgetManagerPtr->RequestSelectOut(TypeId);

		return false;
	}

	return false;
}

void ABattleLevelGameMode::RequestSetCharacterToPtrMap(ACharacter* chara){

	ABaseCharacter* BaseCharacter = Cast<ABaseCharacter>(chara);

	if (IsValid(BaseCharacter)) {
	
		//キャラクターをマップにセットする
		Field->SetCharacterToPtrMap(BaseCharacter);
	
	}
	
}

bool ABattleLevelGameMode::RequestRetreatPlayerCharacter(AActor* actor){

	//受取ったキャラをPlayerCharacterにキャスト。
	//クリックしたアクターがPlayerCharaであればキャストできる
	APlayerCharacter* PlayerChara = Cast<APlayerCharacter>(actor);

	//キャスト出来ていれば、
	if (IsValid(PlayerChara)) {

		//キャラの状態がまだ死亡状態ではなければ
		if (PlayerChara->GetCharacterStatus() == ABaseCharacter::CharacterStatus::kActive) {

			//キャラの状態を死亡状態にする。
			PlayerChara->SetCharacterStatus(ABaseCharacter::CharacterStatus::kDead);

			//キャラのフェーズを撤退フェーズにする。
			PlayerChara->SetCharaPhase(APlayerCharacter::PlayerCharaPhase::kRetreat);

			//攻撃アニメーションを停止する。
			PlayerChara->SetbIsAttackToEnemy(false);

			//ここで削除する前にコストを回復させる。
			//キャラに出撃コストを持たせて、その値の半分を回復させるようにする。
			BattlePlayerState->HealCostForRetreating(PlayerChara->GetNeedCost());

			//コストのUI表示を更新する
			BattleLevelWidgetManagerPtr->UpdateCost(BattlePlayerState->GetNowSpawnCost());

			//撤退モーションの再生通知を出す
			PlayerChara->SetbIsRetreatAnimation(true);

			////キャラの状態を死亡状態にする。
			//PlayerChara->SetCharacterStatus(ABaseCharacter::CharacterStatus::kDead);
			////まずキャラクターの位置を表したマップから、そのキャラのポインタを削除
			//Field->ChangeToNullPtrMapInCharacter(PlayerChara);
			////その後、PlayerCharaをdeleteする
			//PlayerCharaSpawnerPtr->DeletePlayerCharacter(PlayerChara);

			return true;
		}
	}

	return false;
}

bool ABattleLevelGameMode::RequestCheckMapInfo(AActor* actor){

	AEnemyCharacter* enemy = Cast<AEnemyCharacter>(actor);

	if (IsValid(enemy)) {

		//次に移動する座標を受取る変数
		int GotoX = 0;
		int GotoY = 0;
	
		//今敵がいる座標から次に行くべき座標を取得する
		bool check = Field->CheckMapInfoAraundEnemy(*enemy, GotoX, GotoY);

		if (check) {
			//次に移動する座標をセット
			enemy->SetNextXPoint(GotoX);
			enemy->SetNextYPoint(GotoY);

			return true;
		}
		return false;
	}
	return true;
}

void ABattleLevelGameMode::RequestCharacterPtrToNull(ACharacter* chara){

	Field->ChangeToNullPtrMapInCharacter(chara);
}

void ABattleLevelGameMode::RequestSerchEnemy(AActor* actor) {

	//フィールドから返ってくるキャラポインタの配列を受取る変数
	TArray< ABaseCharacter*> BaseCharaArray;
	AEnemyCharacter* Enemy = nullptr;
	APlayerCharacter* PlayerChara = nullptr;
	ABaseCharacter* BaseChara = Cast<ABaseCharacter>(actor);

	if (IsValid(BaseChara)) {

		//索敵処理を呼ぶ
		BaseCharaArray = Field->SerchEnemy(BaseChara);

		//返ってきたキャラのポインタ分配列を回す
		for (int i = 0; i < BaseCharaArray.Num(); i++) {

			if (BaseCharaArray.IsValidIndex(i)) {

				//索敵処理を行ったキャラの種類を確認
				switch (BaseChara->GetCharacterSide()) {

				//味方キャラクターだったら
				case ABaseCharacter::CharacterSide::kPlayer:

					//配列に入っているキャラが敵かどうかをキャストして確かめる
					Enemy = Cast<AEnemyCharacter>(BaseCharaArray[i]);

					//敵であれば
					if (IsValid(Enemy)) {

						//ターゲットにする
						BaseChara->SetTargetEnemy(Enemy);

						//その敵の攻撃されたフラグをtrueにする
						Enemy->SetbIsAttacked(true);
						//敵キャラのターゲットに自身のポインタを入れる
						Enemy->SetTargetEnemy(BaseChara);

						//ターゲットエネミーをもう入れられなければ
						if (BaseChara->GetbIsRimitTarget()) {

							return;
						}
					}

					break;

				//索敵処理を呼んだのが敵だったら
				case ABaseCharacter::CharacterSide::kEnemy:
					
					Enemy = Cast<AEnemyCharacter>(BaseChara);

					//敵のタイプを取得し、分岐させる
					switch (Enemy->GetEnemyType()) {

					//敵自身がノーマルタイプだったら、
					case AEnemyCharacter::EnemyType::kNormal:

						//見つけた敵がプレイヤーかどうかを確認
						PlayerChara = Cast<APlayerCharacter>(BaseCharaArray[i]);

						//キャスト出来ていれば
						if (IsValid(PlayerChara)) {

							//キャストしたキャラとターゲットのキャラが同じであれば
							if (PlayerChara == BaseChara->GetTargetEnemy()) {

								if (IsValid(Enemy)) {

									//もしそのキャラの止められる敵の上限のフラグがtrueなら、
									if (PlayerChara->GetbIsNoMoreStopEnemy() == true) {

										//その味方キャラクターとはバトルを行わずにターゲット配列から外す
										Enemy->DeleteTargetEnemy(PlayerChara);
										//攻撃されたフラグを降ろす
										Enemy->SetbIsAttacked(false);
										continue;
									}

									//止めている敵の数の配列に敵自身を入れる
									PlayerChara->SetEnemyArrayAttackingToThisPlayer(Enemy);

									//現在止めている敵の数が、止められる敵の数の上限に達していないかを見る
									if (PlayerChara->CheckNumAttackingToThisPlayer()) {
										PlayerChara->SetbIsNoMoreStopEnemy(true);
									}
									//敵のバトルフラグを立てる
									Enemy->SetbIsBattle(true);

								}
							}
						}
						break;

					//敵自身が遠距離タイプだったら
					case AEnemyCharacter::EnemyType::kLongRange:

						//見つけた敵がプレイヤーかどうかを確認
						PlayerChara = Cast<APlayerCharacter>(BaseCharaArray[i]);

						//キャスト出来ていれば
						if (IsValid(PlayerChara)) {

							//自身をキャスト
							Enemy = Cast<AEnemyCharacter>(BaseChara);
							//キャスト出来ていれば
							if (IsValid(Enemy)) {

								//まだターゲットを見つけてなければ、
								if (Enemy->GetTargetEnemyNum() == 0) {

									//その味方キャラクターのターゲットの上限がtrueならそのキャラとはバトルしない。
									if (PlayerChara->GetbIsRimitTarget() == true) {

										continue;
									}

									//他の敵キャラに攻撃されていなければ、
									if (!(PlayerChara->GetbIsNoMoreStopEnemy())) {

										//見つけたキャラのポインタを自身のターゲット配列に入れる。
										Enemy->SetTargetEnemy(BaseCharaArray[i]);
										//攻撃を仕掛けている敵の配列に自身を入れる
										PlayerChara->SetEnemyArrayAttackingToThisPlayer(Enemy);
										//敵のバトルフラグを立てる
										Enemy->SetbIsBattle(true);

										//もし止められる敵の数が上限を超えていれば、
										if (PlayerChara->CheckNumAttackingToThisPlayer()) {
											PlayerChara->SetbIsNoMoreStopEnemy(true);
										}
									}
								}
								//プレイヤーキャラから攻撃されて、ターゲットがいる状態であれば、
								else if (Enemy->GetbIsAttacked()) {

									//キャストしたキャラとターゲットのキャラが同じであれば
									if (PlayerChara == BaseChara->GetTargetEnemy()) {

										//もしそのキャラのターゲットの上限のフラグがtrueなら、
										if (PlayerChara->GetbIsNoMoreStopEnemy()) {

											//その味方キャラクターとはバトルを行わずにターゲット配列から外す
											Enemy->DeleteTargetEnemy(PlayerChara);
											Enemy->SetbIsAttacked(false);
											continue;
										}

										//止めている敵の配列に敵自身を入れる
										PlayerChara->SetEnemyArrayAttackingToThisPlayer(Enemy);

										//止めている敵の数の上限に達していれば
										if (PlayerChara->CheckNumAttackingToThisPlayer()) {
											PlayerChara->SetbIsNoMoreStopEnemy(true);
										}
										//敵のバトルフラグを立てる
										Enemy->SetbIsBattle(true);
									}
								}
							}
						  break;
						}
					}
					break;
				}
			}
		}
	}
}

void ABattleLevelGameMode::RequestDeleteCharacter(ACharacter* character) {

	ABaseCharacter* BaseChara = Cast<ABaseCharacter>(character);

	switch (BaseChara->GetCharacterStatus()) {

	case ABaseCharacter::CharacterStatus::kDead:
		if (IsValid(Cast<APlayerCharacter>(character))) {

			//APlayerにキャスト
			APlayerCharacter* Player = Cast<APlayerCharacter>(character);

			//マップ上のポインタを削除
			Field->ChangeToNullPtrMapInCharacter(Player);

			//プレイヤーキャラクラスのスポナーを呼んで削除
			PlayerCharaSpawnerPtr->DeletePlayerCharacter(Player);
		}
		else if (IsValid(Cast<AEnemyCharacter>(character))) {

			//エネミーにキャスト
			AEnemyCharacter* Enemy = Cast<AEnemyCharacter>(character);

			//敵を倒したので、コストを回復させる
			//ここの回復量もエネミーにコストの回復量みたいなパラメーターを持たせて、
			//その値を引き数で渡す予定。ゲームクリア、オーバーのチェックまでのブランチをマージしてもらったらそこを実装します。
			BattlePlayerState->HealCostForDefeatingEnemy(Enemy->GetHealCostForDefeating());

			//コストを回復したので、HUDの方の表示も更新する
			BattleLevelWidgetManagerPtr->UpdateCost(BattlePlayerState->GetNowSpawnCost());

			//マップ上のポインタを削除
			Field->ChangeToNullPtrMapInCharacter(Enemy);

			//エネミーキャラのスポナーを呼んで削除
			EnemySpawnerPtr->DeleteEnemyCharacter(Enemy);

		}

		break;

	case ABaseCharacter::CharacterStatus::kPause:

		if (BaseChara->GetCharacterSide() == ABaseCharacter::CharacterSide::kPlayer) {

			//APlayerにキャスト
			APlayerCharacter* Player = Cast<APlayerCharacter>(character);

			//マップ上のポインタを削除
			Field->ChangeToNullPtrMapInCharacter(Player);

			//プレイヤーキャラクラスのスポナーを呼んで削除
			PlayerCharaSpawnerPtr->DeletePlayerCharacter(Player);
	
		}
		else {
		
			//エネミーにキャスト
			AEnemyCharacter* Enemy = Cast<AEnemyCharacter>(character);

			//マップ上のポインタを削除
			Field->ChangeToNullPtrMapInCharacter(Enemy);

			//エネミーキャラのスポナーを呼んで削除
			EnemySpawnerPtr->DeleteEnemyCharacter(Enemy);
		
		}

		break;
	}
}


void ABattleLevelGameMode::RequestSetBaseCharaInterface(ACharacter* chara) {

	ABaseCharacter* BaseChara = Cast<ABaseCharacter>(chara);

	if (IsValid(BaseChara)) {

		BaseChara->SetBaseCharaInterface(this);

	}

}

void ABattleLevelGameMode::RequestSetEnemyCharaEventInterface(ACharacter* chara){

	AEnemyCharacter* EnemyChara = Cast<AEnemyCharacter>(chara);

	if (IsValid(EnemyChara)) {

		EnemyChara->SetEnemyInterface(this);

	}

}

void ABattleLevelGameMode::RequestUpdatePtr(ACharacter* chara, const int x, const int y){

	AEnemyCharacter* Enemy = Cast<AEnemyCharacter>(chara);

	//キャストが有効なら、
	if (IsValid(Enemy)) {

		//移動前の座標にあるポインタを削除
		Field->ChangeToNullPtrMapInCharacter(Enemy);

		//新しい座標を引き数から貰って敵の座標に更新
		Enemy->SetXPoint(x);
		Enemy->SetYPoint(y);

		//その新しい座標にキャラのポインタを入れる
		Field->SetCharacterToPtrMap(Enemy);
	}
}

TArray<EnemyBasePointStruct::EnemyBasePoint> ABattleLevelGameMode::RequestGetEnemyBasePosition(){

	//敵拠点の座標情報を入れる構造体配列を宣言
	TArray<EnemyBasePointStruct::EnemyBasePoint> EnemyBasePointStructArray;

	//敵拠点を検索
	//見つけた拠点の情報が入った構造体の返り値を返す
	return EnemyBasePointStructArray = Field->SerchEnemySpawnPoint();
}

void ABattleLevelGameMode::RequestDeletePlayerBaseActor(AActor* BaseActor){

	//味方拠点にキャスト
	APlayerBase* PlayerBase = Cast<APlayerBase>(BaseActor);

	//キャストが有効なら、
	if (IsValid(PlayerBase)) {
		//味方拠点配列を回す
		for (int i = 0; i < PlayerBaseArray.Num(); i++) {

			//引き数のアクターと検索した要素が一緒であれば、
			if (PlayerBaseArray[i] == PlayerBase) {

				//アクターを削除
				PlayerBaseArray[i]->Destroy();
				//配列からも消す
				PlayerBaseArray.RemoveAt(i);
			}
		}
	}
}

bool ABattleLevelGameMode::RequestCheckReachPlayerBase(ACharacter* chara){

	//敵キャラにキャスト
	AEnemyCharacter* Enemy = Cast<AEnemyCharacter>(chara);

	//敵キャラであれば、
	if (IsValid(Enemy)) {
		//Fieldクラスの、引き数の敵キャラが拠点に着いたかどうかを確認する関数を呼ぶ。
		bool IsReach = Field->CheckReachPlayerBaseForEnemy(Enemy);

		//着いていれば、
		if (IsReach) {

			//trueを返す
			return true;

		}
		else {

			return false;
		}
	}
	return false;
}

void ABattleLevelGameMode::RequestReachPlayerBaseEvent(ACharacter* chara){

	//敵キャラにキャスト
	AEnemyCharacter* Enemy = Cast<AEnemyCharacter>(chara);

	//キャストが有効であれば、
	if (IsValid(Enemy)) {

		//敵キャラの座標を取得
		int x =Enemy->GetXPoint();
		int y = Enemy->GetYPoint();

		//味方拠点にダメージをあたえる
		//引き数として、敵の座標とダメージ数を与える
		//ダメージ数もここは仮。
		BattleGameState->DamageToBase(Enemy->GetAttack(), x, y);

		//キャラクターのFieldマップからポインタを削除する
		Field->ChangeToNullPtrMapInCharacter(Enemy);
		//拠点に着いた敵キャラはフィールドから消したいので削除する。
		EnemySpawnerPtr->DeleteEnemyCharacter(Enemy);
	}
}


void ABattleLevelGameMode::RequestGiveUpdateTime(float time) {

	//Widgetに更新された時間を渡す
	BattleLevelWidgetManagerPtr->RequestUpdateTime(time);

}

void ABattleLevelGameMode::RequestGiveTickTimetToEnemySpawnerManager(float PassedTime, float DeltaTime) {
	
	//毎フレーム時間を渡してスポーン処理を実行させる
	EnemySpawnerManagerPtr->ExecuteSpawn(PassedTime, DeltaTime);
}


void ABattleLevelGameMode::RequestGameClear() {

	//GameStateのフェーズを終了フェーズにする
	BattleGameState->SetPhase(ABattleLevelGameState::GameStatePhase::kFinish);
	
	//キャラクターの動きを止める
	EnemySpawnerPtr->StopEnemyCharacter(false);
	PlayerCharaSpawnerPtr->StopPlayerCharacter(true);

	//リザルトメッセージに出す文字
	FString message = "Game Clear";
	BattleLevelWidgetManagerPtr->RequestShowMessage(message);

	NowPhase = kPreEnd;

	//４秒後にレベルをロードする
	//FTimerHandle _TimerHandle;
	// GetWorld()->GetTimerManager().SetTimer(_TimerHandle, this, &ABattleLevelGameMode::OpenNextLevel, 4.0f, true);
}

void ABattleLevelGameMode::RequestGameOver() {

	//GameStateのフェーズを終了フェーズにする
	BattleGameState->SetPhase(ABattleLevelGameState::GameStatePhase::kFinish);

	//キャラクターの動きを止める
	EnemySpawnerPtr->StopEnemyCharacter(true);
	PlayerCharaSpawnerPtr->StopPlayerCharacter(false);

	//リザルトメッセージに出す文字
	FString message = "Game Over";
	BattleLevelWidgetManagerPtr->RequestShowMessage(message);


	NowPhase = kPreEnd;
	//４秒後にレベルをロードする
	//FTimerHandle _TimerHandle;
	//GetWorld()->GetTimerManager().SetTimer(_TimerHandle, this, &ABattleLevelGameMode::OpenNextLevel, 4.0f, true);
		
}

void ABattleLevelGameMode::FinishBattleForRetreat(ACharacter* character){

	//味方キャラへキャスト
	APlayerCharacter* PChara = Cast<APlayerCharacter>(character);

	//キャストが成功していれば、
	if (IsValid(PChara)) {
	
		//戦っていた敵キャラを取得
		ABaseCharacter* BaseChara = PChara->GetTargetEnemy();

		//敵クラスへキャスト
		AEnemyCharacter* Enemy = Cast<AEnemyCharacter>(BaseChara);

		//キャストが成功すれば、
		if (IsValid(Enemy)) {
		
			//Enemy->DeleteTargetEnemy(PChara);
			//敵キャラのフェーズをバトルフェーズを終わらせ、どのフェーズへ遷移するかチェックするフェーズへ遷移させる。
			Enemy->SetEnemyPhase(AEnemyCharacter::EnemyPhase::kCheckNextPhase);
		
		}
	}
}

void ABattleLevelGameMode::RequestSetPCharaEventInterface(ACharacter* chara){

	APlayerCharacter* PChara = Cast<APlayerCharacter>(chara);

	if (IsValid(PChara)) {
		
		PChara->SetPCharaEventInterface(this);
	}
}

void ABattleLevelGameMode::RequestChangeColorMaterial(AActor* actor){

	//道のマテリアルの色を赤にする
	Field->CallChangeColorMaterial(actor);
}

void ABattleLevelGameMode::RequestResetColorMaterial(AActor* actor){

	//道のマテリアルの色を戻す
	Field->CallResetColorMaterial();
}

void ABattleLevelGameMode::InformFInishIntroduction() {

	//ゲームUIのWIdgetを開く
	BattleLevelWidgetManagerPtr->OpenWidget();

	//GameStartの表示を行う
	BattleLevelWidgetManagerPtr->RequestShowMessage(TEXT("Game Start"));

	//WIdgetManagerのフェーズをGameStartUIの表示時間を管理するフェーズへ遷移する
	BattleLevelWidgetManagerPtr->SetWidgetManagerPhase(ABattleLevelMainWidgetManager::WidgetManagerPhase::kWaitHideGameStartMessage);
	
	//ゲーム開始前フェーズ
	NowPhase = kPreStart;
}


void ABattleLevelGameMode::OpenNextLevel() {

	//レベルをロードする
	//現状は一つしかないので仮で同じレベル
	UGameplayStatics::OpenLevel(GetWorld(), "TowerDefenseLevel");		
}

void ABattleLevelGameMode::InitializeGameMode(){

	//==============================================================
	//DataManagerから読み取った情報を取得
	//==============================================================
		//DataManagerが存在すれば、
	if (IsValid(DataManagerPtr)) {

		if (IsValid(PlayerCharaSpawnerPtr)) {
			//プレイヤーキャラデータリストを取得しセット
			PlayerCharaSpawnerPtr->SetPlayerStatusDataList(DataManagerPtr->GetPlayerCharaList());

			//プレイヤーキャラのスポナーにインターフェースのポインタを渡す
			PlayerCharaSpawnerPtr->SetSpawnerInterface(this);
			PlayerCharaSpawnerPtr->SetCharacterSpawnerInterface(this);
		}

		//==============================================================
		//敵のスポナーとそのマネージャーの初期化
		//==============================================================

		if (IsValid(EnemySpawnerPtr)) {
			//敵キャラデータリストを取得しセット
			EnemySpawnerPtr->SetEnemyStatusDataList(DataManagerPtr->GetEnemyCharaList());

			//敵キャラのスポナーにインターフェースを渡す
			EnemySpawnerPtr->SetEnemySpawnerInterface(this);
			EnemySpawnerPtr->SetCharacterSpawnerInterface(this);

		}

		if (IsValid(EnemySpawnerManagerPtr)) {
			//Wave情報リストを取得しセット
			EnemySpawnerManagerPtr->SetEnemyWaveInfoList(DataManagerPtr->GetWaveInfoList());

		}
	}

	if (IsValid(Field)) {

		//生成したマップチップのアクターにインターフェースを渡す
		Field->RequestSetMapChipInterface(this);
	}


	//==============================================================
	//生成する敵キャラのBPクラスをロードする
	//==============================================================
		//ゲームンスタンスを取得する
	UTowerDefenseGameInstance* GameInstance = Cast<UTowerDefenseGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	//ゲームインスタンスが存在すれば
	if (IsValid(GameInstance)) {
		//ゲームインスタンスのEnemyBaseChipPathを取得する。
		FString EnemyCharacterPath = GameInstance->GetEnemyCharacterPath();
		//EnemyBaseChipPathクラスを取得する。
		TSubclassOf<AActor>EnemyCharacterClass = TSoftClassPtr<ACharacter>(FSoftObjectPath(*EnemyCharacterPath)).LoadSynchronous();
	}

	//==============================================================
	//BattleLevelで使うWIdgetの初期化
	//==============================================================

		//BattleLevelControllerにキャスト
	BattleLevelControllerPtr = Cast<ABattleLevelController>(UGameplayStatics::GetPlayerController(this, 0));
	//キャストが成功すれば
	if (IsValid(BattleLevelControllerPtr)) {

		//HUDをBattleLevelWidgetManagerにキャストする
		BattleLevelWidgetManagerPtr = Cast<ABattleLevelMainWidgetManager>(BattleLevelControllerPtr->GetHUD());
		//キャストが成功すれば
		if (IsValid(BattleLevelWidgetManagerPtr)) {
			//インターフェースを渡す
			BattleLevelWidgetManagerPtr->SetInterface(this);

			//アイコンの情報構造体の配列
			TArray<CharacterIconInfoStruct::IconInfo> IconInfoArray;

			//宣言した構造体配列に値を代入する
			SetCharacterIconInfoArray(IconInfoArray);

			//WidgetManagerにゲーム説明に必要な情報をDataManagerから渡す
			BattleLevelWidgetManagerPtr->SetIntroductionInfoArray(DataManagerPtr->GetIntroductionPageInfo());

			//WidgetManagerにアイコンに必要な情報をDataManagerから渡す
			BattleLevelWidgetManagerPtr->SetIconInfoArray(IconInfoArray);

			//Managerを初期化し、WIdgetに必要なWidgetの生成などを行う。
			BattleLevelWidgetManagerPtr->InitializeMainWidgetManager();

			//BattlePlayerStateに初期化
			BattlePlayerState = Cast<ABattlePlayerState>(BattleLevelControllerPtr->GetPlayerState<ABattlePlayerState>());

			//有効であれば、
			if (IsValid(BattlePlayerState)) {

				//DataManagerのポインタがあれば、
				if (IsValid(DataManagerPtr)) {

					//プレイヤー自身に関わるデータ構造体を取得。
					BattlePlayerStateStruct::PlayerStateData PStateData = DataManagerPtr->GetPlayerStateStructData();

					//コストの最大値を取得
					float MaxCost = PStateData.MaxSpawnCost;
					//ここでCSVから読み取ったコストの最大値をセットする。
					BattlePlayerState->Initialize(MaxCost);

					/// Widgetの方にもコストの表示を反映させる
					BattleLevelWidgetManagerPtr->InitializeCostDisplay(MaxCost);
				}
			}
		}

		//キャストしたウィジェットマネージャに実装されたインターフェースをコントローラーに渡す
		BattleLevelControllerPtr->SetWidgetManagerEventInterface(BattleLevelWidgetManagerPtr);
		BattleLevelControllerPtr->SetInterface(this);

		//マウスカーソルを出す
		BattleLevelControllerPtr->bShowMouseCursor = true;
		//マウスカーソルによって実行されるイベントを有効にするためにフラグをtrueにする
		BattleLevelControllerPtr->bEnableClickEvents = true;
		BattleLevelControllerPtr->bEnableMouseOverEvents = true;

		//ウィジェットを開く
		BattleLevelControllerPtr->RequestOpenWidget();

		//カメラアクターがBattleLevelBPにセットされていれば、
		if (IsValid(FieldCamera)) {
			//そのカメラの視点を使う
			BattleLevelControllerPtr->SetViewTarget(FieldCamera);
		}
	}

	//==============================================================
	//GameStateの初期化。時間や拠点の数など
	//==============================================================

		//BattleGameStateにキャスト
	BattleGameState = GetGameState<ABattleLevelGameState>();

	//キャストが有効であれば、
	if (IsValid(BattleGameState)) {

		if (IsValid(DataManagerPtr)) {
			//まずインターフェースを渡す
			BattleGameState->SetBattleGameStateInterface(this);

			//制限時間もCSVで読み取ってここにセットするようにする。
			// 現状はマジックナンバーになっているが、後で直す予定。
			BattleGameState->SetLimitTime(DataManagerPtr->GetLimitTime());

			//フィールドに拠点の情報をもらう。
			TArray<PlayerBaseDataStruct::PlayerBaseData> PlayerBaseStructArray = Field->SerchPlayerBase();

			//その構造体の数だけ拠点を生成
			for (auto BaseStruct : PlayerBaseStructArray) {

				//拠点を生成と同時にワールドにスポーンする。
				APlayerBase* PlayerBase = GetWorld()->SpawnActor<APlayerBase>();

				//構造体から情報を取得し初期化していく。
				//拠点のX座標
				PlayerBase->SetXPoint(BaseStruct.XPoint);
				//拠点のY座標
				PlayerBase->SetYPoint(BaseStruct.YPoint);
				//拠点のIDをセット
				PlayerBase->SetId(BaseStruct.BaseId);
				//拠点のHPもセット。
				//ここも仮の引き数。コストの情報がか書かれたCSVに拠点のHPの項目を追加して、そこから読み出す予定
				//ここもゲームクリアオーバーのブランチまでマージ頂いてから実装します。
				PlayerBase->SetHp(DataManagerPtr->GetPlayerStateStructData().PlayerBaseHp);

				//HpBarWidgetのクラスを渡し、最大HPなどを初期化。
				PlayerBase->Initialize(PlayerBaseHpBarWidgetClass);

				//構造体から、ワールドでの座標を取得し、ベクターの構造体を初期化。
				FVector BaseLocation(BaseStruct.XPointInWorld, BaseStruct.YPointInWorld, BaseStruct.ZPointInWorld);

				//味方拠点の位置を更新する
				PlayerBase->SetActorLocation(BaseLocation);

				//味方拠点の配列に格納する
				PlayerBaseArray.Add(PlayerBase);
			}

			//配列にいれた拠点をGameStateに渡す。
			BattleGameState->SetPlayerBaseArray(PlayerBaseArray);
		}
	}

	//==============================================================
	//EnemySpawnerManagerの初期化。
	//==============================================================

	if (IsValid(EnemySpawnerManagerPtr)) {

		//EnemySpawnerManagerにSpawnerのポインタをセットする
		EnemySpawnerManagerPtr->SetEnemySpawner(EnemySpawnerPtr);
		//Managerのインターフェースをセットする
		EnemySpawnerManagerPtr->SetESpwnerManagerInterface(this);
		//敵のリスポーン地点を検索して、取得しセット
		EnemySpawnerManagerPtr->SetEnemyBasePointList();

	}

	//フェーズをゲーム説明フェーズに遷移。
	NowPhase = kIntroduction;
}


/////////////////////////////////////////////////////////////////////////////////////////
// 毎フレーム処理
////////////////////////////////////////////////////////////////////////////////////////

void ABattleLevelGameMode::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);

	bool ChcekbIsFInishShowGameStartUI = false;

	switch(NowPhase) {

	//ゲーム説明フェーズ
	case kIntroduction:

		//IntroductionWidgetからのCloseのイベント通知を受取ったタイミングで、kPreStartフェーズへ遷移する

		break;
	
	//ゲーム開始前フェーズ
	case kPreStart:

		//WidgetManagerに毎フレーム時間を渡して、ManagerにUI表示の開始や終了などの管理を行わせる
		ChcekbIsFInishShowGameStartUI = BattleLevelWidgetManagerPtr->PreStartWidgetProcessing(DeltaTime);

		//GameStartのUI表示が終わっていれば、
		if (ChcekbIsFInishShowGameStartUI) {
		
			/*==============================================================
			GameStateのTickのフェーズを動かして、スポーンを開始する。
			==============================================================*/
			
			//GameStateがあれば。
			if (IsValid(BattleGameState)) {

			////制限時間を初期化する
		    BattleGameState->StartTimer();
			////GameStateのフェーズを時間計測のフェーズに変える
		    BattleGameState->SetPhase(ABattleLevelGameState::GameStatePhase::kTimer);

			//リスポーンを開始。
			EnemySpawnerManagerPtr->SetSpawnerManagerPhase(AEnemySpawnerManager::EnemySpawnerManagerPhase::kSpawning);

			//ゲームモードのフェズをゲーム処理中に変える
			NowPhase = kProcessing;
			}
		
		}
		break;

	case kProcessing:

		//ゲームモードでは特に何もしない
		//EnemySpawnManagerがTickを回して敵の生成を行ってゲームを進行

		break;

	//ゲーム終了前フェーズ
	//ゲーム終了の条件になったら遷移する
	case kPreEnd:

		//GameOverかGameClearの表示が終わっていれば、
		if (BattleLevelWidgetManagerPtr->RequestGetbIsFinishShowMessage()) {

			//リザルトボタンの表示を行う
			BattleLevelWidgetManagerPtr->RequestShowButton();

			//終了フェーズへ遷移する
			NowPhase = kEnd;
		}

		break;

	case kEnd:


		break;
	};

}

void ABattleLevelGameMode::BeginPlay() {
	Super::BeginPlay();

	//if(!bIsInitializeGameMode)
	InitializeGameMode();
	
}

void ABattleLevelGameMode::SetCharacterIconInfoArray(TArray<CharacterIconInfoStruct::IconInfo>& IconInfoArray){

	//DataManagerが存在すれば、
	if (IsValid(DataManagerPtr)) {
		//プレイヤーキャラデータリストを取得しセット
		TArray<CharacterStruct::CharaStruct> CharaInfoArray = DataManagerPtr->GetPlayerCharaList();

		//キャラクターの情報構造体配列を回す
		for (int i = 0; i < CharaInfoArray.Num(); i++) {
		
			//構造体のキャラの敵か味方の変数が味方キャラであれば、
			if (CharaInfoArray[i].CharaSide == kPlayerCharaSide) {
			
				//各種変数にキャラクター情報構造体から情報を取得。
				//アイコン構造体を宣言
				CharacterIconInfoStruct::IconInfo IconInfo;
				//必要コスト
				IconInfo.NeedCost = CharaInfoArray[i].NeedCost;
				//キャラの種類
				IconInfo.TypeId = CharaInfoArray[i].TypeId;
				//キャラアイコンに設定する画像のパス
				IconInfo.IconTexture = CharaInfoArray[i].IconPath;
				//キャラのHP
				IconInfo.Hp = CharaInfoArray[i].Hp;
				//キャラの攻撃力
				IconInfo.Attack = CharaInfoArray[i].Attack;
				//キャラの防御力
				IconInfo.Defense = CharaInfoArray[i].Defense;
				//キャラの攻撃スピード
				IconInfo.AttackSpan = CharaInfoArray[i].AttackSpan;
				//キャラのXの索敵範囲
				IconInfo.XRange = CharaInfoArray[i].XRange;
				//キャラのYの索敵範囲
				IconInfo.YRange = CharaInfoArray[i].YRange;
				//索敵範囲の開始範囲
				IconInfo.StartSerchRangeNum = CharaInfoArray[i].StartSerchRangeNum;
				//止められる敵の数
				IconInfo.StopEnemyNum = CharaInfoArray[i].StopEnemyNum;

				//アイコン構造体配列に生成した構造体を入れる
				IconInfoArray.Push(IconInfo);
			}
		}
	}
}
