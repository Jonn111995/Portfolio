// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "BattlePlayerState.generated.h"

/**
 * 
 */
UCLASS()
class ABattlePlayerState : public APlayerState
{
	GENERATED_BODY()

public:

	/// <summary>
	/// コストの最大値をセットし、その最大値を現在のコスト変数にも代入する関数を呼ぶ
	/// </summary>
	void Initialize(float MaxCost);

	/// <summary>
	/// コストの最大値をセットする
	/// </summary>
	void SetMaxSpawnCost(float cost) { MaxSpawnCost = cost; };

	/// <summary>
	/// 現在のコストにコストの最大値をセットする
	/// </summary>
	void SetSpawnCost() { NowSpawnCost = MaxSpawnCost; };

	/// <summary>
	/// 現在の残りコストを取得
	/// </summary>
	/// <returns></returns>
	float GetNowSpawnCost() { return NowSpawnCost; };

	/// <summary>
	/// 現在のコストが0かどうかを確認する
	/// </summary>
	/// <returns></returns>
	bool CheckNowSpawnCost(float cost);

	/// <summary>
	/// 現在のコストが最大値を超えていないかを確認し、
	/// 超えていたら、最大値に強制的にする。
	/// </summary>
	void CheckOverMaxSpawnCostNum();

	/// <summary>
	/// 現在のコストから消費したコストを引く。
	/// </summary>
	/// <param name="cost"></param>
	void SubtractCost(float cost);

	/// <summary>
	/// 撤退したときにコストを回復させる処理
	/// </summary>
	/// <param name="cost"></param>
	void HealCostForRetreating(float cost);

	/// <summary>
	/// 敵キャラを倒したときにコストを回復させる処理
	/// </summary>
	/// <param name="cost"></param>
	void HealCostForDefeatingEnemy(float cost);

private:
	
	/// <summary>
	/// 最大のコスト
	/// </summary>
	float MaxSpawnCost;

	/// <summary>
	/// 現在のコスト
	/// </summary>
	float NowSpawnCost;

	/// <summary>
	/// コストが0であることを示す
	/// </summary>
	const float EmptyCost = 0.0f;

	/// <summary>
	/// 撤退したときに回復するコストを計算する。
	/// </summary>
	const float kAdjustNumForHealinRetreating = 2.0f;
	
};
