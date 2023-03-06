// Fill out your copyright notice in the Description page of Project Settings.


#include "BattleLevel/CharacterClass/DefenseCharacter.h"

void ADefenseCharacter::SetTargetEnemy(ABaseCharacter* chara) {

	//ターゲットの上限を超えていれば
	if (bIsRimitTarget) {
	
		return;
	}

	if (IsValid(chara)) {

		//ターゲットエネミー配列にまだ誰も入っていなければ、
		if (TargetEnemy.Num() == 0) {

			//引き数のキャラをターゲットにする
			TargetEnemy.Add(chara);
		}
		//ターゲットに敵が存在していて、
		else{

			for (int i = 0; i < TargetEnemy.Num(); i++) {

				if (TargetEnemy.IsValidIndex(i)) {

					if (IsValid(TargetEnemy[i])) {

						//まだターゲット配列に引き数のキャラが存在しなければ、
						if (TargetEnemy[i] != chara) {

							//引き数のキャラをターゲットにする
							TargetEnemy.Add(chara);

						}
					}
				}
			}

			//ターゲットの上限になれば、
			if (TargetEnemy.Num() >= StopEnemyNum) {
				//ターゲットを入れないフラグをONにする
				bIsRimitTarget = true;
			}
		}
	}
}

void ADefenseCharacter::Tick(float DeltaTime) {

	Super::Tick(DeltaTime);

	//キャラが死んでいたら、処理させない
	switch(NowStatus){

	case kActive:

		if (NowCharaPhase == APlayerCharacter::PlayerCharaPhase::kBattle) {

			//ターゲットがもうすでに一体以上はいて、
			if (TargetEnemy.Num() != 0) {

				//かつ、止められる敵の数にまだ余裕があり、
				if (bIsNoMoreStopEnemy == false) {

					//さらにターゲットの配列にもまだ入れられれば
					if (bIsRimitTarget == false) {

						//索敵処理をする
						BaseCharacterInterface->RequestSerchEnemy(this);
					}
				}
			}

		}

		//BaseCharacterのTickを実行する
		APlayerCharacter::Tick(DeltaTime);

		break;
	}
}
