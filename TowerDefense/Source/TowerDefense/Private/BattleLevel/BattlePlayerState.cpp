// Fill out your copyright notice in the Description page of Project Settings.


#include "BattleLevel/BattlePlayerState.h"
#include "BattlePlayerState.h"

void ABattlePlayerState::Initialize(float MaxCost) {

	//コストの最大値をセット
	SetMaxSpawnCost(MaxCost);

	//現在のコストを最大値にセット
	SetSpawnCost();
}

bool ABattlePlayerState::CheckNowSpawnCost(float cost){

	//現在のコストが0以下であれば
	if (NowSpawnCost <= EmptyCost) {
	
		//falseを返す
		return false;
	}
	//消費するコストを引いた結果0を下回るなら
	else if ((NowSpawnCost-cost) < 0) {
	
	
		return false;
	}
	else {

		//そうでなければ
		return true;
	}

	return false;
}

void ABattlePlayerState::CheckOverMaxSpawnCostNum(){

	//現在のコストがコストの最大値を超えたら、
	if (NowSpawnCost > MaxSpawnCost) {
	
		//現在のコストを最大値とする
		NowSpawnCost = MaxSpawnCost;
	}
}

void ABattlePlayerState::SubtractCost(float cost){

	//現在のこコストから引く
	NowSpawnCost -= cost;
}

void ABattlePlayerState::HealCostForRetreating(float cost){

	//プレイヤーのコスト量の半分を計算
	float HealPoint = cost / kAdjustNumForHealinRetreating;

	//計算した回復量を現在のコストに足す
	NowSpawnCost += HealPoint;

	//回復した結果、最大値を超えているかどうかを確認
	CheckOverMaxSpawnCostNum();

}

void ABattlePlayerState::HealCostForDefeatingEnemy(float cost){

	//現在のコストに引き数の値を足す
	NowSpawnCost += cost;

	//コストの最大値を超えていないか確認
	CheckOverMaxSpawnCostNum();
}
