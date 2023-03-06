// Fill out your copyright notice in the Description page of Project Settings.


#include "BattleLevel/CharacterClass/LongRangeAttackEnemy.h"


void ALongRangeAttackEnemy::SerchEnemy() {

	if (IsValid(HpWidget)) {

		HpWidget->UpdatePhaseDisplay(TEXT("索敵中"));

		//遠距離タイプの敵は常に索敵処理をして、見つけ次第攻撃する
		BaseCharacterInterface->RequestSerchEnemy(this);
	}
}