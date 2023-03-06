// Fill out your copyright notice in the Description page of Project Settings.


#include "BattleLevel/EnemyCharacter.h"
#include "Kismet/KismetMathLibrary.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"

#include "AIController.h"


//void AEnemyCharacter::AddGoToDirection(CharacterDirection direction){
//
//	CanGoToList.Add(direction);
//}


AEnemyCharacter::AEnemyCharacter() {

	AttackSpan = 1.0f;
	SerchXRange = 1;
	SerchYRange = 1;
	HP = 30;
	CharaSide = kEnemy;
}

void AEnemyCharacter::CaluculateTargetLocation() {

	//移動する目標の座標を計算
	//Ｘ座標はUEで生成したマップのアクターの位置がすべて-の値なので、マイナスを掛ける
	NewPosition.X = (NextXPoint * 100.0f) * -1;
	//マップチップのサイズ分値を掛ける
	NewPosition.Y = NextYPoint * 100.0f;
	//Ｚは固定
	NewPosition.Z = 100;

}

void AEnemyCharacter::UpdateLocation(float& AbsDifferX, float& AbsDifferY, float DeltaTime) {

	//現在の位置を取得
	NowLocation = this->GetActorLocation();

	//現在の位置を更新用の変数に代入
	UpDatedLocation = NowLocation;

	//現在位置と目標の座標の差の値を計算し、その絶対値を出す。
	//絶対値を出す理由は、そうでない場合、計算結果が-になる場合があり、
	//そうなると0より大きいという条件を満たさずに更新がされない為
	float DifferX = NowLocation.X - NewPosition.X;
	float DifferY = NowLocation.Y - NewPosition.Y;
	AbsDifferX = UKismetMathLibrary::Abs(DifferX);
	AbsDifferY = UKismetMathLibrary::Abs(DifferY);

	//更新用のキャラクターの回転値に、現在の回転値を代入する
	FRotator CharaRotate = GetActorRotation();

	//Ｘ座標の差を計算
	//絶対値が0以上、つまりまだ目的地に着いていなければ、
	if (AbsDifferX > 0) {

		//マップの下方向に進んだ場合
		//現在-次の座標なので下に行く場合はX座標が大きくなるので、計算結果がマイナスになる
		if (DifferX < 0) {
		
			//歩くスピードの値を座標位置に足す
			UpDatedLocation.X += WalkSpeed;

			//元々キャラの向きは下方向なのでそのまま
			CharaRotate.Yaw = 0.0f;

		}
		//マップの上方向へ進んだ場合
		else if (DifferX > 0) {

			//歩くスピードの値を座標から引く
			UpDatedLocation.X -= WalkSpeed;

			//キャラの向きを真反対に向けたいので180度回転
			CharaRotate.Yaw = 180.0f;

		}
	}

	//絶対値が0以上、つまりまだ目的地に着いていなければ、
	if (AbsDifferY > 0) {

		//現在-次の座標なので右に行く場合はY座標が大きくなるので、計算結果がマイナスになる
		if (DifferY < 0) {

			//右方向へ行くのでY座標に足す
			UpDatedLocation.Y += WalkSpeed;
			//下向きから右向きにしたいので、90度回転
			CharaRotate.Yaw = 90.0f;

		}
		else if (DifferY > 0) {

			//左方向へ行くので、Y座標から引く
			UpDatedLocation.Y -= WalkSpeed;
			//下向きから左向きにしたいので、-90度回転
			CharaRotate.Yaw = -90.0f;
		}

	}

	//更新された位置の値をキャラクターにセットする
	this->SetActorLocation(UpDatedLocation);

	//現在の回転値と、更新したキャラの回転値が異なれば、
	if (GetActorRotation() != CharaRotate) {

		//キャラの回転値を代入する。少しずつ変えるようにしている
		SetActorRotation(FMath::RInterpTo(GetActorRotation(), CharaRotate, DeltaTime, 1.0f*WalkSpeed));

	}
}

void AEnemyCharacter::UpdateMapPtr() {

	////マップに格納されたキャラクターのポインタをnullにする
	//CSpawnInterface->RequestCharacterPtrToNull(this);

	////新しい座標をキャラクターに代入
	//XPoint = NextXPoint;
	//YPoint = NextYPoint;

	////新しい座標に、キャラのポインタを入れる
	//CSpawnInterface->RequestSetCharacterToPtrMap(this);

}

void AEnemyCharacter::SerchEnemy(){

	HpWidget->UpdatePhaseDisplay(TEXT("索敵中"));

	//味方キャラクターからの攻撃を受けていれば、
	if (bIsAttacked) {

		//BattleFieldで敵キャラが索敵範囲にいるかどうかを探す。
		BaseCharacterInterface->RequestSerchEnemy(this);

	}

}



void AEnemyCharacter::SetTargetEnemy(ABaseCharacter* chara) {

	//同じキャラが存在しないか確認するフラグ
	bool CheckSameCharaExist = false;

	for (int i = 0; i < TargetEnemy.Num(); i++) {

		if (IsValid(TargetEnemy[i])) {

			//同じキャラが配列にいれば、
			if (TargetEnemy[i] == chara) {

				//フラグを立てる
				CheckSameCharaExist = true;

				break;
			}
		}
	}

	//同じキャラがいるかどうかのフラグが経っていなければ、
	if (!CheckSameCharaExist) {
		//引き数のキャラをターゲットにする
		TargetEnemy.Add(chara);
	}
}

void AEnemyCharacter::DeleteTargetEnemy(ABaseCharacter* Chara){

	if (IsValid(Chara)) {
	
		for (int i = 0; i < TargetEnemy.Num(); i++) {
		
			if (IsValid(TargetEnemy[i])) {

				//一致するキャラクターがターゲット配列にいれば、
				if (Chara == TargetEnemy[i]) {

					//そのキャラを配列から削除する
					TargetEnemy.RemoveAt(i);
				}
			}
		
		}
	
	}
}

void AEnemyCharacter::BeginPlay() {
	Super::BeginPlay();

	NowPhase = kCheckSrounding;
}

void AEnemyCharacter::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);

	//コンポーネントからWidgetのポインタを取得し、関数などを使えるようにキャスト。
	HpWidget = Cast<UHpBarWidget>(HpBarWidget->GetWidget());

	//次の座標が得られたかどうか
	bool IsGetNextPoint = false;
	//ターゲットエネミーが死亡したかどうか
	bool IsDeadTargetEnemy = false;
	//味方拠点に着いたかどうか
	bool IsReachBase = false;
	float DifferenceDistanceX = 0.0f;
	float DifferenceDistanceY = 0.0f;
	FRotator TargetRotate;

	//HpBarのキャストが成功していれば、
	if (IsValid(HpWidget)) {

		//現在のステータスを確認
		switch (NowStatus) {

			//生きていれば
		case kActive:

			//攻撃されている状態であれば、
			if (bIsBattle && !(NowPhase == kCheckNextPhase)) {

				//バトルフェーズへ
				NowPhase = kBattle;
			}

			//現在のキャラの行動フェーズを確認
			switch (NowPhase) {

				//次に移動する座標の確認フェーズ
			case kCheckSrounding:

				//フィールドの情報を確認し、次に移動するべきマスを確認する
				IsGetNextPoint = EnemyInterface->RequestCheckMapInfo(this);

				//次の座標が取得できれば、
				if (IsGetNextPoint) {

					//ワールドの座標計算フェーズへ遷移
					NowPhase = kDecidePosition;
				}

				break;

				//ワールドの座標計算フェーズ
			case kDecidePosition:

				CaluculateTargetLocation();

				//移動フェーズへ
				NowPhase = kWalking;

				break;

				//移動フェーズ
			case kWalking:

				//まだ味方キャラから攻撃されていなければ
				if (!bIsAttacked) {
					//移動中と表示
					HpWidget->UpdatePhaseDisplay(TEXT("移動中"));
				}
			//	HpWidget->UpdateTargetNumDisplay(TargetEnemy.Num());
				//毎フレームの時間を足していく。
				CountTime += DeltaTime;

				//経過した時間が更新時間以上になったら、
				if (CountTime >= time) {

					//ターゲットの配列で無効になったものが無いか確認
					for (int i = 0; i < TargetEnemy.Num(); i++) {

						//無効なものがあれば、
						if (!(IsValid(TargetEnemy[i]))) {

							//配列から削除する
							TargetEnemy.RemoveAt(i);

						}
					}

					//索敵処理を実行する
					SerchEnemy();

					//ワールドでの位置を更新する
					UpdateLocation(DifferenceDistanceX, DifferenceDistanceY, DeltaTime);

					if (DifferenceDistanceX <= 0 && DifferenceDistanceY <= 0) {

						//Fieldのポインタマップを更新する
						EnemyInterface->RequestUpdatePtr(this, NextXPoint, NextYPoint);
						IsReachBase = EnemyInterface->RequestCheckReachPlayerBase(this);

						if (IsReachBase) {

							//bIsReachAnimation = true;
							//UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), ReachEffect, GetActorLocation());
							EnemyInterface->RequestReachPlayerBaseEvent(this);
						}

						//次に移動する座標を探す
						NowPhase = kCheckSrounding;

					}
					//経過時間をリセットする
					CountTime = 0.0f;

				}
				break;

			//バトルフェーズ
			case kBattle:

				HpWidget->UpdatePhaseDisplay(TEXT("バトル中"));
				//ターゲットの数を表示
				//HpWidget->UpdateTargetNumDisplay(TargetEnemy.Num());
				ArrowMesh->SetVisibility(true);

				if (TargetEnemy.IsValidIndex(kFirstAttackEnemyIndex)) {

					FVector AScale = ArrowMesh->GetComponentScale();
					AScale.Y = (GetHorizontalDistanceTo(TargetEnemy[kFirstAttackEnemyIndex]) / kAjustNumAttackArrowSize);
					ArrowMesh->SetWorldScale3D(AScale);
				
					//毎フレーム時間を足して、経過時間を計測
					CountTimeForAttack += DeltaTime;

					//キャラを敵の方向へ向ける
					TargetRotate = UKismetMathLibrary::FindLookAtRotation(GetActorLocation(), TargetEnemy[kFirstAttackEnemyIndex]->GetActorLocation());
					SetActorRotation(FMath::RInterpTo(GetActorRotation(), TargetRotate, DeltaTime, kTurnRate));

					//経過時間が、攻撃の間隔時間以上になったら、
					if (CountTimeForAttack >= AttackSpan) {

						//攻撃アニメーションを再生
						bIsAttackToEnemy = true;

						//攻撃処理を呼ぶ
						IsDeadTargetEnemy = GiveDamage();

						CountTimeForAttack = 0.0f;
						//もし敵キャラが死亡したら、
						if (IsDeadTargetEnemy || !(IsValid(TargetEnemy[kFirstAttackEnemyIndex]))) {

							ArrowMesh->SetVisibility(false);

							//ターゲット配列からその敵キャラを外す
							TargetEnemy.RemoveAt(kFirstAttackEnemyIndex);

							//次にどのフェーズへ行くかを確認するフェーズへ
							NowPhase = kCheckNextPhase;
						}
					}
				}
				break;

			//次にどのフェーズへ行くかを確認するフェーズへ
			//バトルフェーズが終わった後、または味方キャラがバトル中に撤退してキャラがいなくなった後に遷移するフェーズ
			case kCheckNextPhase:

				HpWidget->UpdatePhaseDisplay(TEXT("フェーズ変更中"));

				//攻撃アニメーションを停止
				bIsAttackToEnemy = false;

				for (int i = 0; i < TargetEnemy.Num(); i++) {

					//キャラのポインタが有効かどうか確認
					if (IsValid(TargetEnemy[i])) {

						//ターゲットがもう死亡していれば、
						if (TargetEnemy[i]->GetCharacterStatus() == ABaseCharacter::CharacterStatus::kDead) {

							//ターゲットから外す
							TargetEnemy.RemoveAt(i);

						}
					}
					//有効で無ければ配列から削除
					else {

						TargetEnemy.RemoveAt(i);
					}
				}

				//攻撃するターゲットがいなければ、
				if (TargetEnemy.Num() == 0) {

					//現在の位置と目標の位置との差を計算する
					DifferenceDistanceX = UKismetMathLibrary::Abs(NowLocation.X - NewPosition.X);
					DifferenceDistanceY = UKismetMathLibrary::Abs(NowLocation.Y - NewPosition.Y);

					//攻撃されているフラグを停止
					bIsAttacked = false;
					//バトルしているフラグを停止
					bIsBattle = false;

					//その差が0以上であれば、
					if (DifferenceDistanceX > 0 || DifferenceDistanceY > 0) {

						//歩くフェーズに戻って、処理を再開する
						NowPhase = kWalking;
					}
					else {

						//そうでなければ、次に移動する座標を探す
						NowPhase = kCheckSrounding;
					}
				}
				//ターゲットが存在していて、かつバトルフェーズ遷移フラグが立っていれば
				else if (bIsBattle == true) {

					//バトルフェーズを続行
					NowPhase = kBattle;
				}

				break;

			}


			break;

			//死亡後のフェーズ
		case kDead:
			HpWidget->UpdatePhaseDisplay(TEXT("倒された！"));

			//死亡アニメーションの再生通知
			bIsDeadAnimation = true;

			//アニメーションの再生終了通知を受取ったら
			if (bIsFinishDeathAnimation) {

				//自身を削除
				BaseCharacterInterface->RequestDeleteCharacter(this);
				NowStatus = kAfterDead;
			}

			break;

			//ゲーム自体が終了した後のフェーズ
		case kPause:

			//攻撃アニメーションの停止通知
			bIsAttackToEnemy = false;

			//敵側が負けた場合に、死亡アニメーションを再生するので、その終了通知を受取ったら、
			if (bIsFinishDeathAnimation) {

				//自身を削除する
				BaseCharacterInterface->RequestDeleteCharacter(this);
				NowStatus = kAfterDead;

			}

			break;

		case kAfterDead:

			break;
		}

	}
}
