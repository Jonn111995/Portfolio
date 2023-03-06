// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "PlayerBase.h"
#include "../BattleLevel/Interface/BattleGameStateEventInterface.h"
#include "BattleLevelGameState.generated.h"

/**
 * 
 */
UCLASS()
class ABattleLevelGameState : public AGameStateBase
{
	GENERATED_BODY()

public:

	/// <summary>
	/// GameStateのフェーズ
	/// </summary>
	enum GameStatePhase {

		//何もなし
		kNone,

		//時間計測フェーズ
		kTimer, 

		//終了フェーズ
		kFinish 
		
	};

	
	/// <summary>
	/// コンストラクタ
	/// </summary>
	ABattleLevelGameState();

	/// <summary>
	/// 味方拠点の配列をセット
	/// </summary>
	void SetPlayerBaseArray(TArray<APlayerBase*> BaseArray) { PlayerBaseArray = BaseArray; };
	/// <summary>
	/// GameStateのインターフェース
	/// </summary>
	/// <param name="Interface"></param>
	void SetBattleGameStateInterface(IBattleGameStateEventInterface* Interface) { BattleGameStateInterface = Interface; };

	/// <summary>
	/// GameStateのフェーズのセッター
	/// </summary>
	/// <param name="phase"></param>
	void SetPhase(GameStatePhase phase) { NowPhase = phase; };
	GameStatePhase GetPhase() { return NowPhase; };

	/// <summary>
	/// PlayerBaseにダメージを与える
	/// </summary>
	/// <param name="damage">ダメージ数</param>
	/// <param name="x">敵のX座標</param>
	/// <param name="y">敵のY座標</param>
	void DamageToBase(int damage,int x, int y);

	/// <summary>
	/// 制限時間の開始時間をセット
	/// </summary>
	/// <param name="time"></param>
	void SetLimitTime(float time) { LimitSeconds = time; };

	/// <summary>
	/// 現在の時間の制限時間の開始時間をセットする
	/// </summary>
	void StartTimer();

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

private:

	/// <summary>
	/// 制限時間の開始時間
	/// </summary>
	float LimitSeconds;

	/// <summary>
	/// 開始時間
	/// </summary>
	float StartTime;
		
	/// <summary>
	/// 現在の時間
	/// </summary>
	float NowTime;
	
	/// <summary>
	/// ゲームをクリアしたかどうかのフラグ
	/// </summary>
	bool GameClear = false;

	/// <summary>
	/// 全ての拠点が無くなったことを示す
	/// </summary>
	const int kAllBaseDestroy = 0;

	/// <summary>
	/// 残り時間が無くなったことを示す
	/// </summary>
	const float kNoLeftLimitiTime = 0.0f;
		
	/// <summary>
	/// GameStateの現在のフェーズ
	/// </summary>
	GameStatePhase NowPhase;
		
	/// <summary>
	/// 味方拠点の配列
	/// </summary>
	TArray<APlayerBase*> PlayerBaseArray;

	/// <summary>
	/// BattleGameStateのインターフェース
	/// </summary>
	IBattleGameStateEventInterface* BattleGameStateInterface;

};
