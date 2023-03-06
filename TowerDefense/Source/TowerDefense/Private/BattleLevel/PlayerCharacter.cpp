// Fill out your copyright notice in the Description page of Project Settings.


#include "BattleLevel/PlayerCharacter.h"
#include "Kismet/KismetMathLibrary.h"
#include "Components/ArrowComponent.h"
#include "Components/CapsuleComponent.h"


APlayerCharacter::APlayerCharacter() {

	
}

void APlayerCharacter::SetEnemyArrayAttackingToThisPlayer(ABaseCharacter* Enemy){

	//配列の要素数が止められる敵の数より少なければ
	if (EnemyArrayAttackingToThisPlayer.Num() < StopEnemyNum) {

		//配列に入れる
		EnemyArrayAttackingToThisPlayer.Push(Enemy);
	}
}

bool APlayerCharacter::CheckNumAttackingToThisPlayer(){

	//止めている敵の数が、止められる敵の数より大きければ
	if (EnemyArrayAttackingToThisPlayer.Num() >= StopEnemyNum) {
	
		//もう止められないとしてtrueにする
		return true;
	}
	else {
	
		return false;
	}


	return false;
}

void APlayerCharacter::BindFunction(){

	FScriptDelegate Delegate;
	FScriptDelegate Delegate2;

	Delegate.BindUFunction(this, TEXT("ShowRetreatUI"));
	UCapsuleComponent* capsule = GetCapsuleComponent();
	capsule->OnBeginCursorOver.Add(Delegate);

	Delegate2.BindUFunction(this, TEXT("HideRetreatUI"));
	capsule->OnEndCursorOver.Add(Delegate2);
}

void APlayerCharacter::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);

	HpWidget = Cast<UHpBarWidget>(HpBarWidget->GetWidget());
	//ターゲットキャラが死んでいるかどうかの変数
	bool IsDeadTargetEnemy = false;
	//敵キャラへ向く目標の回転値
	FRotator TargetRotate;
	
	//現在のキャラのステータス状態を確認
	switch (NowStatus) {

	//生きていれば
	case kActive:

		//現在の行動フェーズを確認
		switch (NowCharaPhase) {

		//スポーンした時のフェーズ
		case kSpawn:

			//HPWIdgetの上に現在のフェーズを表示
			HpWidget->UpdatePhaseDisplay(TEXT("スポーン中"));

			//ABPの方で、スポーンアニメーションの終了通知を受取ったら、
			if (bIsFinishSpawnAnimation) {

				BindFunction();
				//索敵フェーズへ
				NowCharaPhase = kSerch;
			}

			break;

		//索敵フェーズ
		case kSerch:

			//HPWIdgetの上に現在のフェーズを表示
			HpWidget->UpdatePhaseDisplay(TEXT("索敵中"));
			//ターゲットの敵数を表示
		//	HpWidget->UpdateTargetNumDisplay(TargetEnemy.Num());
			//ここで索敵の処理を呼ぶ
			//インターフェースを実装したゲームモードにイベント通知を行って、フィールドの情報を確認する。自身のポインタを渡す
			BaseCharacterInterface->RequestSerchEnemy(this);
			ArrowMesh->SetVisibility(false);

			//ゲームモードの処理の中で、ターゲットにキャラが追加されていれば、
			if (!(TargetEnemy.Num() == 0)) {

				//かつターゲットの0番目のポインタが有効であれば、
				if (TargetEnemy.IsValidIndex(kFirstAttackEnemyIndex)) {

					if (IsValid(TargetEnemy[kFirstAttackEnemyIndex])) {
						//バトルフェーズに遷移する
						NowCharaPhase = kBattle;
					}
				}
			}
			break;

		//バトルフェーズ
		case kBattle:



			//HPWIdgetの上に現在のフェーズを表示
			HpWidget->UpdatePhaseDisplay(TEXT("バトル中"));
			//ターゲットの敵数を表示
			//HpWidget->UpdateTargetNumDisplay(TargetEnemy.Num());
			//攻撃を仕掛けられている敵の数を表示
			//HpWidget->UpdateAttackingEnemyNumDisplay(EnemyArrayAttackingToThisPlayer.Num());
			//毎フレーム時間を足して、経過時間を計測
			CountTimeForAttack += DeltaTime;

			//ターゲット配列の一番目があれば、
			if (TargetEnemy.IsValidIndex(kFirstAttackEnemyIndex)) {

				//かつそのポインタが有効であれば、
				if (IsValid(TargetEnemy[kFirstAttackEnemyIndex])) {

					ArrowMesh->SetVisibility(true);

						FVector AScale = ArrowMesh->GetComponentScale();
						AScale.Y = (GetHorizontalDistanceTo(TargetEnemy[kFirstAttackEnemyIndex])/ kAjustNumAttackArrowSize);
						ArrowMesh->SetWorldScale3D(AScale);
						
						bIsShowArrow = true;
			
					//敵の方向へ向かせる処理
					TargetRotate = UKismetMathLibrary::FindLookAtRotation(GetActorLocation(), TargetEnemy[kFirstAttackEnemyIndex]->GetActorLocation());
					SetActorRotation(FMath::RInterpTo(GetActorRotation(), TargetRotate, DeltaTime, kTurnRate));

					//経過時間が、攻撃の間隔時間以上になったら、
					if (CountTimeForAttack >= AttackSpan) {

						//ターゲットが自身の攻撃範囲にいるかどうかを確認する
						bool CheckEnemyInRange = CheckEnemyPositionInRange();

						//索敵範囲から離れていれば、
						if (CheckEnemyInRange) {

							//攻撃アニメーションを停止通知
							bIsAttackToEnemy = false;

							//ターゲット配列からその敵キャラを外す
							TargetEnemy.RemoveAt(kFirstAttackEnemyIndex);

							//配列の要素数が減って、ターゲットを入れられる上限を下回れば、
							if (TargetEnemy.Num() < StopEnemyNum) {

								//リミットのフラグを降ろす
								bIsRimitTarget = false;
							}

							//索敵フェーズへ遷移
							NowCharaPhase = kSerch;
							return;
						}

						//攻撃アニメーションの再生通知
						bIsAttackToEnemy = true;

						//攻撃処理を呼ぶ
						IsDeadTargetEnemy = GiveDamage();

						//経過時間をリセットする
						CountTimeForAttack = 0.0f;

						//もし敵キャラが死亡したら、
						if (IsDeadTargetEnemy) {

							//攻撃アニメーションの停止通知
							bIsAttackToEnemy = false;
						//	ArrowMesh->SetVisibility(false);

							//止めている敵の数の配列を回す
							for (int i = 0; i < EnemyArrayAttackingToThisPlayer.Num(); i++) {

								//ターゲットと同じ、キャラを止めている敵の数の配列から探し、
								if (TargetEnemy[kFirstAttackEnemyIndex] == EnemyArrayAttackingToThisPlayer[i]) {

									//見つかれば配列から削除
									EnemyArrayAttackingToThisPlayer.RemoveAt(i);

									//削除した結果、止められる敵の数を、配列数が下回れば
									if (EnemyArrayAttackingToThisPlayer.Num() < StopEnemyNum) {

										//敵をまだ止められるかのフラグを降ろす
										bIsNoMoreStopEnemy = false;
									}

									//ターゲット配列からその敵キャラを外す
									TargetEnemy.RemoveAt(kFirstAttackEnemyIndex);

									//止められる敵の数よりターゲットが下回れば
									if (TargetEnemy.Num() < StopEnemyNum) {

										//上限をfalseにする
										bIsRimitTarget = false;
									}
									//索敵フェーズへ遷移
									NowCharaPhase = kSerch;
								}
							}
						}
					}

				}
				//ポインタが有効でなければ、
				else {
				
					//ターゲット配列からその敵キャラを外す
					TargetEnemy.RemoveAt(kFirstAttackEnemyIndex);
					ArrowMesh->SetVisibility(false);

					//配列の要素数が減って、ターゲットを入れられる上限を下回れば、
					if (TargetEnemy.Num() < StopEnemyNum) {

						//リミットのフラグを降ろす
						bIsRimitTarget = false;

						//索敵フェーズへ遷移
						NowCharaPhase = kSerch;
					}
				}
			}
				break;

		
		}

		//case::kActiveのbreak
		break;

	//死亡フェーズ
	case kDead:

		if (NowCharaPhase == kRetreat) {

			//HPWIdgetの上に現在のフェーズを表示
			HpWidget->UpdatePhaseDisplay(TEXT("撤退中！"));

			//戦っていた敵がいれば、その敵のフェーズをバトルフェーズから、次にどのフェーズへいくかをチェックするフェーズへ遷移する
			PCharaEventInterface->FinishBattleForRetreat(this);

			//ターゲットの数が一体以上いれば
			if (TargetEnemy.Num() != 0) {

				if (IsValid(TargetEnemy[kFirstAttackEnemyIndex])) {
					//ターゲット配列からその敵キャラを外す
					TargetEnemy.RemoveAt(kFirstAttackEnemyIndex);
				}
			}

			//自身を削除するイベント通知をゲームモードへ行う。
			BaseCharacterInterface->RequestDeleteCharacter(this);

		}
		else {
			HpWidget->UpdatePhaseDisplay(TEXT("倒された！"));

			//死亡アニメーションの再生通知をON
			bIsDeadAnimation = true;

			//死亡アニメーションの終了通知がくれば
			if (bIsFinishDeathAnimation) {

				//自身を削除
				BaseCharacterInterface->RequestDeleteCharacter(this);

				NowStatus = kAfterDead;
			}

		}
		break;

	//ゲーム終了時のフェーズ
	case kPause:

		//攻撃アニメーションの停止通知
		bIsAttackToEnemy = false;

		if (bIsFinishDeathAnimation) {

			BaseCharacterInterface->RequestDeleteCharacter(this);
			NowStatus = kAfterDead;
		}

		break;

	case kAfterDead:
		//デバック用
		HpWidget->UpdatePhaseDisplay(TEXT("AfterDead"));
		break;
	}
}

void APlayerCharacter::ShowRetreatUI(){

	if (IsValid(HpWidget)) {
	
		HpWidget->CallShowRetreatUI();
	}

}

void APlayerCharacter::HideRetreatUI(){

	if (IsValid(HpWidget)) {

		HpWidget->CallHideRetreatUI();

	}

}

bool APlayerCharacter::CheckEnemyPositionInRange(){

	//ターゲットの０番目が有効であれば、
	if (TargetEnemy.IsValidIndex(kFirstAttackEnemyIndex)) {

		//ターゲットの座標を取得
		int EnemyX = TargetEnemy[kFirstAttackEnemyIndex]->GetXPoint();
		int EnemyY = TargetEnemy[kFirstAttackEnemyIndex]->GetYPoint();

		//ターゲットと自身の座標の差の絶対値を計算
		int DifferX = UKismetMathLibrary::Abs(XPoint - EnemyX);
		int DifferY = UKismetMathLibrary::Abs(YPoint - EnemyY);

		//X座標の差が索敵範囲より大きければ
		if (DifferX > SerchXRange) {

			return true;
		}
		//Y座標の差が索敵範囲より小さければ、
		else if (DifferY > SerchYRange) {

			return true;
		}
		//どれでも無ければ、索敵範囲にいるとしてfalseを返す
		else {

			return false;
		}
	}
	return false;
}
